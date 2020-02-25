#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "queue.h"

int inside_queue[HARDWARE_NUMBER_OF_FLOORS]={0};
int up_queue[HARDWARE_NUMBER_OF_FLOORS]= {0};
int down_queue[HARDWARE_NUMBER_OF_FLOORS]={0};
static int required_floors[HARDWARE_NUMBER_OF_FLOORS]={-1,-1,-1,-1};


int check_order_at_current_floor(){
    for(int i= 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i) && (hardware_read_order(i, HARDWARE_ORDER_UP)||hardware_read_order(i,HARDWARE_ORDER_DOWN))){
        return 1;
        }
    }
    return 0;
}

int order_at_last_floor(int *p_last_floor){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(up_queue[i]||down_queue[i]||inside_queue[i]){
            if(i == *p_last_floor){
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

void make_required_floors(){
    for(int i= 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(inside_queue[i]){
            required_floors[i] =i;
        }
    }  
}

void delete_required_floors(const int* p_last_floor){
    required_floors[*p_last_floor] =-1;
}

void print_req_floors(){
    for(int i = 0; i< HARDWARE_NUMBER_OF_FLOORS; i++){
        printf("%d", up_queue[i]);
    }

}



/*
int required_floor(const int* p_last_floor, const int* p_lastMotorDirection) {
    if(*p_lastMotorDirection){
        for(int i = 0;i < HARDWARE_NUMBER_OF_FLOORS;i++){
            if(required_floors[i]>=*p_last_floor){
                for(int j =0; j<HARDWARE_NUMBER_OF_FLOORS; j++){
                    //if ((j>*p_last_floor)&&(j<required_floors[i])){
                        if(up_queue[j]){
                            return j;
                            }
                        //}
                    }
                    
                return required_floors[i];
            }
        }
    }
        for(int i = HARDWARE_NUMBER_OF_FLOORS-1;i >=0 ;i--){
            if((required_floors[i]<=*p_last_floor) && (required_floors[i]>=0)){
                return required_floors[i];
            }
        }
    

    if(!*p_lastMotorDirection){
        for(int i = HARDWARE_NUMBER_OF_FLOORS-1;i >=0 ;i--){
            if((required_floors[i]<=*p_last_floor) && (required_floors[i]>=0)){
                for(int j =HARDWARE_NUMBER_OF_FLOORS-1; j>=0; j--){
                    //if ((j>*p_last_floor)&&(j<required_floors[i])){
                        if(down_queue[j]){
                            return j;
                            }
                        //}
                    }
                return required_floors[i];
            }
        }
        
        for(int i = 0;i < HARDWARE_NUMBER_OF_FLOORS;i++){
            if(required_floors[i]>=*p_last_floor){
            return required_floors[i];
            }
        }
            
        
        
    }
    return -2;
}
*/

int check_order_above(const int* p_last_floor){
    for(int i = 0; i< HARDWARE_NUMBER_OF_FLOORS; i++){
        if( up_queue[i] || down_queue[i] || inside_queue[i]){
            if(i > *p_last_floor){
                return 1;
            }
        }
    }
    return 0;
}

int check_order_below(const int* p_last_floor){
    for(int i = 0; i< HARDWARE_NUMBER_OF_FLOORS; i++){
        if( up_queue[i] || down_queue[i] || inside_queue[i]){
            if(i < *p_last_floor){
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

