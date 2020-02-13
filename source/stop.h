/**
 * @file
 * @brief Module for stopping the elevator.
 *
 *
 * Pauline M. Jonassen & Helene E. Haugen
 */

/**
 * @brief Checks if the stopbutton is pushed, if so stop the elevator.
 */
void set_emergency_stop();

/**
 * @brief If the sensor @p floor is active stop the elevator. 
 * @param floor, the floor we want to stop at. 
 */

void set_floor_stop(int floor);