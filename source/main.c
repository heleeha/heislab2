#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "lights.h"
#include "door.h"
#include "stop.h"
#include "queue.h"
#include "fsm.h"

static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

static int lastfloor;
static int lastMotorDirection;

int main(){
 

    signal(SIGINT, sigint_handler);
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

     int error = hardware_init();
        if(error != 0){
            fprintf(stderr, "Unable to initialize hardware\n");
            exit(1);
        }

    State change_state = INIT;
    
    while(1){

        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
            }
    switch (change_state)
    {
    case INIT:
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        lastMotorDirection =1;

        for( int i = 0; i<HARDWARE_NUMBER_OF_FLOORS; i++){
            if (hardware_read_floor_sensor(i)){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP); 
                current_floor();
                change_state = STILL;
            }
        }
        break;
   
    case STILL:
        add_to_queue();
        set_floor_light();
        set_order_light_on();
        current_floor();
        if(order_in_queues()){
            change_state = MOVING;
        } 
        if(hardware_read_stop_signal()){
            change_state = EMERGENCY_STOP;
        }
        if(check_order_at_current_floor()){
            set_start_time();
            change_state = DOOR;
        }
        break;

    case MOVING:
        add_to_queue();
        make_required_floors();
        update_last_floor(&lastfloor);
        set_order_light_on();
        set_floor_light();
        //print_req_floors();
        

        if(check_and_return_floor_inside()>= 0){
           if(lastfloor < required_floor(&lastfloor,&lastMotorDirection)){
               hardware_command_movement(HARDWARE_MOVEMENT_UP);
               lastMotorDirection =1;
           }
        
           else if ((lastfloor > required_floor(&lastfloor,&lastMotorDirection)) && (lastfloor>=0)){
               hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
               lastMotorDirection =0;
           }
           else if(current_floor() == required_floor(&lastfloor,&lastMotorDirection)) {
               set_start_time();
               change_state = DOOR;
           }
        }

        if(lastfloor < required_outside_floor(&lastfloor,&lastMotorDirection)){
               hardware_command_movement(HARDWARE_MOVEMENT_UP);
               lastMotorDirection =1;
        }
        
        else if ((lastfloor > required_outside_floor(&lastfloor,&lastMotorDirection)) && (lastfloor>=0)){
               hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
               lastMotorDirection =0;
        }
        else if(current_floor() == required_outside_floor(&lastfloor,&lastMotorDirection)) {
               set_start_time();
               change_state = DOOR;
        }
        

       
        if(hardware_read_stop_signal()){
            change_state = EMERGENCY_STOP;
        }

        break;

    case DOOR:
        
        delete_order();
        delete_required_floors(&lastfloor);
        
        set_order_light_off();
        set_order_light_on();
        add_to_queue();
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        if(counting_3seconds()){
            hardware_command_door_open(1);
            if (hardware_read_obstruction_signal()) {
                hardware_command_door_open(1);
                set_start_time();
                change_state = DOOR;
            }
        }
        else {
        hardware_command_door_open(0);
        change_state = STILL;
        }
        break;

    case EMERGENCY_STOP:
        clear_all_order_lights();
        set_emergency_stop();
        delete_all_orders();
        set_stop_light();
        break;

    default:
        break;
    }
}           
}