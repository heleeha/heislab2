/**
 * @file
 * @brief Module for engine.
 *
 *
 * Pauline M. Jonassen & Helene E. Haugen
 */
#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "engine.h"


int read_emergency_stop(){
	if(hardware_read_stop_signal()){
            return 1;		
	}
    return 0;	
	
}

void move_up(){
	hardware_command_movement(HARDWARE_MOVEMENT_UP);
}

void move_down(){
	hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
}

void move_stop(){
	hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}