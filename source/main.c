/**
 * @file
 * @brief Module for main.
 *
 *
 * Pauline M. Jonassen & Helene E. Haugen
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "fsm.h"

static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}


int main(){

    signal(SIGINT, sigint_handler);
    
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    State changestate = INIT;

    state_machine(changestate);        
    
}
