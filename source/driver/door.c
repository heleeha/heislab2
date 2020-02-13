#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "door.h"
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

void door_obstruction(){
    while(hardware_read_obstruction_signal()) {
        hardware_command_door_open(1);
    }
}