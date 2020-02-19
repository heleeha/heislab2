#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "queue.h"

int outside_queue [][2];
int inside_queue[];


//må kanskje endre hardwareorder til en int, for å få en liste med bare int.
int add_order_to_outside_queue(int floor, HardwareOrder order_type){
    int lenght = len(outside_queue);
    outside_queue[lenght][0] = floor;
    outside_queue[lenght][1]= order_type;
    return outside_queue;
}

int add_order_to_inside_queue(int floor){
    int lenght = len(inside_queue);
    inside_queue[lenght]=floor;
    return inside_queue;
}

int add_to_queue(){
    for(int i = 0; i<HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_order(i,HARDWARE_ORDER_UP)){
            add_order_to_queue(i,0);
        }
        if(hardware_read_order(i,HARDWARE_ORDER_DOWN)){
            add_order_to_queue(i,2);
        }
        if(hardware_read_order(i, HARDWARE_ORDER_INSIDE)){
            add_order_to_inside_queue(i);
        }
    }
}

