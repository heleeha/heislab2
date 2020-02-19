#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "stop.h"

void set_emergency_stop(){
	if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
			
	}	
	
}


void set_floor_stop(int floor){
	if (hardware_read_floor_sensor(floor)){
		hardware_command_movement(HARDWARE_MOVEMENT_STOP);
	}
}
