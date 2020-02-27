/**
 * @file
 * @brief Module for queue.
 *
 *
 * Pauline M. Jonassen & Helene E. Haugen
 */

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

int order_at_last_floor(int last_floor){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(up_queue[i]||down_queue[i]||inside_queue[i]){
            if(i == last_floor){
                return 1;
            }
        
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

void delete_order(int last_floor){
	up_queue[last_floor] =0;
    down_queue[last_floor]=0;
    inside_queue[last_floor]=0;
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



void update_last_floor( int* p_last_floor){
    int floor = current_floor();
    if(floor >= 0 ){
        *p_last_floor = floor;
    }
}


int check_order_above(int last_floor){
    for(int i = 0; i< HARDWARE_NUMBER_OF_FLOORS; i++){
        if( up_queue[i] || down_queue[i] || inside_queue[i]){
            if(i > last_floor){
                return 1;
            }
        }
    }
    return 0;
}

int check_order_below(int last_floor){
    for(int i = 0; i< HARDWARE_NUMBER_OF_FLOORS; i++){
        if( up_queue[i] || down_queue[i] || inside_queue[i]){
            if(i < last_floor){
                return 1;
            }
        }
    }
    return 0;
}



int up_button_at_current_floor(int *p_last_floor){
    int floor = current_floor();
    if (floor>=0){
        if(up_queue[floor]){
            *p_last_floor = floor;
            return 1;
        }
    }
    return 0;
}

int down_button_at_current_floor(int *p_last_floor){
    int floor = current_floor();
    if (floor >= 0){
        if(down_queue[floor]){
            *p_last_floor = floor;
            return 1;
        }
    }
    return 0;
}

int cab_button_at_current_floor(int *p_last_floor){
    int floor = current_floor();
    if(floor>= 0){
        if(inside_queue[floor]){
            *p_last_floor = floor;
            return 1;
        }
    }
    return 0;
}

