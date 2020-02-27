/**
 * @file
 * @brief Module for the state machine.
 *
 *
 * Pauline M. Jonassen & Helene E. Haugen
 */

#ifndef FSM_H
#define FSM_H
/**
 * @brief States used in @c state_machine.
 */
typedef enum {
    INIT,
    IDLE,
    MOVING,
    DOOR,
    EMERGENCY_STOP,
    AFTER_STOP_BETWEEN_FLOORS
} State;

/**
 * @brief A while loop containing a switch with all the states.
 * @param change_state whis is a enum type State.
 */
void state_machine(State change_state);

#endif
