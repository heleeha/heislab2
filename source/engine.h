/**
 * @file
 * @brief Module for engine.
 *
 *
 * Pauline M. Jonassen & Helene E. Haugen
 */
#ifndef ENGINE_H
#define ENGINE_H


/**
 * @brief Checks if the stopbutton is pushed, if so stops the elevator.
 * @return 1 if stop button is pushed, and 0 otherwise.
 */
int read_emergency_stop();

/**
 * @brief makes the elevator move up.
 */
void move_up();

/**
 * @brief makes the elevator move down.
 */
void move_down();

/**
 * @brief makes the elevator stop.
 */
void move_stop();

#endif