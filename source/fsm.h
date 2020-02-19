typedef enum {
    STILL,
    MOVING,
    DOOR,
    EMERGENCY_STOP
} State;

State change_state;


void state_machine();