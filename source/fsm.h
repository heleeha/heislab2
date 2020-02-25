/**
 * @file
 * @brief Module for the state machine.
 *
 *
 * Pauline M. Jonassen & Helene E. Haugen
 */

/**
 * @brief States used in @c state_machine.
 */
typedef enum {
    INIT,
    STILL,
    MOVING,
    DOOR,
    EMERGENCY_STOP,
    EMERGENCY_STOP_BETWEEN_FLOORS
} State;

/**
 * @brief A while loop containing a switch with all the states.
 */
void state_machine(State change_state);