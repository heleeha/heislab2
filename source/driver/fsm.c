#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "lights.h"
#include "stop.h"
#include "queue.h"
#include "fsm.h"

/*

void state_machine(State change_state) {
    switch (change_state)
    {
    case INIT:
        int error = hardware_init();
        if(error != 0){
            fprintf(stderr, "Unable to initialize hardware\n");
            exit(1);
        }
        hardware_command_movement(HARDWARE_MOVEMENT_UP);

        for( int i = 0; i<HARDWARE_NUMBER_OF_FLOORS; i++){
            if (hardware_read_floor_sensor(i)){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);    
            }
        }
        break;
    case STILL:
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        add_to_queue();
        set_floor_light();
        set_order_light_on();
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
        hardware_command_movement(HARDWARE_ORDER_DOWN);
        set_order_light_on();
        set_order_light_off();
        set_floor_light();

        if(hardware_read_floor_sensor(0)){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }
        

        if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }

        if(hardware_read_stop_signal()){
            change_state = EMERGENCY_STOP;
        }
        if(hardware_read_floor_sensor(1)){
            set_start_time();
            change_state = DOOR;
        }

        break;
    case DOOR:
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        if(counting_3seconds()){
            hardware_command_door_open(1);
            change_state = STILL;
        }
        else {
        hardware_command_door_open(0);
        door_obstruction();
        }
    case EMERGENCY_STOP:
        set_emergency_stop();
        delete_all_orders();
        set_stop_light();
        


    default:
        break;
    }
}*/