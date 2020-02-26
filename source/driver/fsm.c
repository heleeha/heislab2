#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "lights.h"
#include "stop.h"
#include "queue.h"
#include "fsm.h"

static int lastfloor;
static int lastMotorDirection;

void state_machine(State change_state) {
    while(1){
    
    switch (change_state)
    {
    case INIT:
        clear_all_order_lights();
        move_up();
        lastMotorDirection =1;

        if (current_floor()>=0){
                move_stop(); 
                change_state = STILL;
            
        }
        break;
   
    case STILL:
        add_to_queue();
        set_floor_light();
        set_order_light_on();
        update_last_floor(&lastfloor);
        
        if(read_emergency_stop()){
            change_state = EMERGENCY_STOP;
        }

        else if(order_in_queues()){
            change_state = MOVING;
        } 
        
        else if(check_order_at_current_floor()){
            set_start_time();
            change_state = DOOR;
        }
        if(read_emergency_stop()){
            change_state = EMERGENCY_STOP;
        }
        break;

    case MOVING:
        add_to_queue();
        
        set_order_light_on();
        set_floor_light();
        
        if(read_emergency_stop()){
            change_state = EMERGENCY_STOP;
        }
        

        if (lastMotorDirection){
            if(check_order_above(lastfloor)){
                move_up();
                lastMotorDirection = 1; 
            }
            else if (check_order_below(lastfloor)){
                move_down();
                lastMotorDirection = 0;
            }
        }
        else if (!lastMotorDirection){
            if(check_order_below(lastfloor)){
                move_down();
                lastMotorDirection = 0;
            }
            else if(check_order_above(lastfloor)){
                move_up();
                lastMotorDirection = 1;
            }
        }
        
        update_last_floor(&lastfloor);


        if(cab_button_at_current_floor(&lastfloor)){
            set_start_time();
            change_state = DOOR;
        }
        else if(lastMotorDirection){
            if(up_button_at_current_floor(&lastfloor)){
                set_start_time();
                change_state= DOOR;
            }
        
            else if(!check_order_above(lastfloor)){
                if(current_floor()>=0){
                    set_start_time();
                    change_state = DOOR;
                }
            } 
        }
        else if(!lastMotorDirection){
            if(down_button_at_current_floor(&lastfloor)){
                if(current_floor()>=0){
                    set_start_time();
                    change_state = DOOR;
                }
            }
            else if(!check_order_below(lastfloor)){
                set_start_time();
                change_state = DOOR; 
            }
            
        }

        
        
        if(read_emergency_stop()){
            change_state = EMERGENCY_STOP;
        }

        break;

    case DOOR:
        delete_order(lastfloor);
        
        set_order_light_off();
        set_order_light_on();
        add_to_queue();
        move_stop();
        if(read_emergency_stop()){
            change_state = EMERGENCY_STOP;
        }
        if(counting_3seconds()){
            open_door();
            if (read_obstruction()){
                open_door();
                set_start_time();
                change_state = DOOR;
            }
        }
        
        else {
        close_door();
        change_state = STILL;
        }
        break;

    case EMERGENCY_STOP:
        clear_all_order_lights();
        move_stop();
        delete_all_orders();
        set_stop_light();
        if(current_floor()>= 0){
            hardware_command_door_open(1);
        }
        if(hardware_read_stop_signal()){
            change_state = EMERGENCY_STOP; 
        }
        else if(current_floor()>= 0){
            clear_stop_light();
            set_start_time();
            change_state = DOOR;
        }
        else if(current_floor()==-1){
            clear_stop_light();
            change_state = EMERGENCY_STOP_BETWEEN_FLOORS;
        }
        else{
            clear_stop_light();
            change_state = STILL;
        }
        break;

    case EMERGENCY_STOP_BETWEEN_FLOORS:
        add_to_queue();
        set_order_light_on();
        update_last_floor(&lastfloor);

        if(hardware_read_stop_signal()){
            change_state = EMERGENCY_STOP;
        }
        if(order_at_last_floor(lastfloor)){
            if(lastMotorDirection == 1){
                move_down();
                if (current_floor()==lastfloor){
                    set_start_time();
                    change_state = DOOR;
                }
            }
            else if(lastMotorDirection == 0){
                move_up();
                if (current_floor()==lastfloor){
                    set_start_time();
                    change_state = DOOR;
                }
            }
        }

        if ((order_in_queues()) && (!order_at_last_floor(lastfloor))){
            change_state = STILL;
        }
        
        break;


    default:
        break;
    }
    }
} 