#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "stop.h"
#include <time.h>

clock_t start;

void set_start_time(){
    start = clock();
}

clock_t get_start_time(){
    return start;
}

int counting_3seconds(){
	
   clock_t begin = get_start_time();

   clock_t difference = clock() - begin;
   int diff_sec = difference/CLOCKS_PER_SEC;

   if (diff_sec > 2) {
       return 0;
   }
   return 1;

} 

void set_emergency_stop(){
	if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
			
	}	
	
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
