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

int order_in_queues(){
    for(int i= 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(inside_queue[i]||up_queue[i]||down_queue[i]){
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

int current_floor(){
    for (int i=0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
		if (hardware_read_floor_sensor(i)) {
            return i;
        }
    }
    return -1;
}



int check_and_return_floor_inside(){
    for(int i= 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(inside_queue[i]){
            return i;
        }
    }
    return -1;
}

int check_and_return_floor_up(){
    for(int i= 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(up_queue[i]){
            return i;
        }
    }
    return -1;
}

int check_and_return_floor_down(){
    for(int i= 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(down_queue[i]){
            return i;
        }
    }
    return -1;
}

void update_last_floor( int* p_last_floor){
    int floor = current_floor();
    if(floor >= 0 ){
        *p_last_floor = floor;
    }
}

