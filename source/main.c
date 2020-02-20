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
int lastfloor;

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

            //state_machine(change_state);

        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
            }
    switch (change_state)
    {
    case INIT:
        hardware_command_movement(HARDWARE_MOVEMENT_UP);

        for( int i = 0; i<HARDWARE_NUMBER_OF_FLOORS; i++){
            if (hardware_read_floor_sensor(i)){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP); 
                last_floor();
                change_state = STILL;
            }
        }
        break;
   
    case STILL:
        add_to_queue();
        set_floor_light();
        set_order_light_on();
        last_floor();
        if(any_order()){
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
        if (last_floor() >= 0) {
            lastfloor = last_floor();
        }
        set_order_light_on();
        set_order_light_off();
        set_floor_light();
        add_to_queue();
        if(check_and_return_floor_inside()>= 0){
           if(lastfloor < check_and_return_floor_inside()){
               hardware_command_movement(HARDWARE_MOVEMENT_UP);
           }
           else if (lastfloor > check_and_return_floor_inside()){
               hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
           }
           else {
               change_state = DOOR;
           }
        }
        if(hardware_read_stop_signal()){
            change_state = EMERGENCY_STOP;
        }

        break;
/*
        if(hardware_read_floor_sensor(0)){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }
        
        if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }*/

    case DOOR:
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        if(counting_3seconds()){
            hardware_command_door_open(1);
            door_obstruction();
        }
        else {
        hardware_command_door_open(0);
        change_state = STILL;
        }
    case EMERGENCY_STOP:
        clear_all_order_lights();
        set_emergency_stop();
        delete_all_orders();
        set_stop_light();
        


    default:
        break;
    }
}           
}