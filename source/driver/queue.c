#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "queue.h"


int inside_queue[HARDWARE_NUMBER_OF_FLOORS]={0};
int up_queue[HARDWARE_NUMBER_OF_FLOORS]= {0};
int down_queue[HARDWARE_NUMBER_OF_FLOORS]={0};

int check_order_at_current_floor(){
    for(int i= 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i) && (hardware_read_order(i, HARDWARE_ORDER_UP)||hardware_read_order(i,HARDWARE_ORDER_DOWN))){
        return 1;
        }
    }
    return 0;
}

int any_order(){
    for(int i= 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_order(i,HARDWARE_ORDER_UP)){
        return 1;
        }
    }
    return 0;
}

void add_to_queue(){
    for(int i = 0; i<HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_order(i,HARDWARE_ORDER_UP)){
            up_queue[i]=1;
            
        }
        if(hardware_read_order(i,HARDWARE_ORDER_DOWN)){
            down_queue[i]=1;
            
        }
        if(hardware_read_order(i, HARDWARE_ORDER_INSIDE)){
            inside_queue[i]=1;
            
        }
    }
    
}

void delete_order(){
	for (int i=0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
		if (hardware_read_floor_sensor(i)) {
			up_queue[i] =0;
            down_queue[i]=0;
            inside_queue[i]=0;
		}
	}
}

void delete_all_orders(){
    for (int i=0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
		up_queue[i] =0;
        down_queue[i]=0;
        inside_queue[i]=0;
	}
}

