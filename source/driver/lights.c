#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "lights.h"

void set_order_light_on(){

	
	for (int i=0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
			if (hardware_read_order(i, HARDWARE_ORDER_UP)) {
				hardware_command_order_light(i, HARDWARE_ORDER_UP, 1);
			}
			if (hardware_read_order(i, HARDWARE_ORDER_DOWN)) {
				hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 1);
			}
			if (hardware_read_order(i, HARDWARE_ORDER_INSIDE)) {
				hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 1);
			}


	}
	
}

void set_order_light_off(){
	for (int i=0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
		if (hardware_read_floor_sensor(i)) {
			hardware_command_order_light(i, HARDWARE_ORDER_UP, 0);
			hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 0);
			hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
		}
	}
}

void set_floor_light(){
	for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
		if (hardware_read_floor_sensor(i)) {
			hardware_command_floor_indicator_on(i);
		}
	}
}


void set_stop_light(){
	if (hardware_read_stop_signal()) {
		hardware_command_stop_light(1);
	}
}

//static void clear_all_order_lights(){
    //HardwareOrder order_types[3] = {
        //HARDWARE_ORDER_UP,
        /*HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}
*/

