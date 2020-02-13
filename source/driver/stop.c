#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "stop.h"
#include <time.h>

void set_emergency_stop{
	if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
	}	
}

void set_delay(int number_of_seconds){
	int milli_seconds = 1000 * number_of_seconds;
	clock_t start_time= clock();
	while(clock() < start_time + milli_seconds){
	}
}

set_floor_stop(){

}
