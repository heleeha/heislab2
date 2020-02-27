/**
 * @file
 * @brief Module for timer and door.
 *
 *
 * Pauline M. Jonassen & Helene E. Haugen
 */
#ifndef DOOR_H
#define DOOR_H

#include <time.h>

/**
 * @brief checks if begin is grater than 2.
 * @return 0 if @p diff_sec is bigger than 2 and otherwise returns 1.
 */
int counting_3seconds();

/**
 * @brief local function returns the starttime. 
 * @return start time which is a clock_t.
 */
clock_t get_start_time();

/**
 * @brief sets @p start to the current clocktime.
 * @param[out] start.
 */
void set_start_time();

/**
 * @brief checks if the obstruction switch is active.
 * @return 1 if it is active or 0 if not.
 */
int read_obstruction();

/**
 * @brief opens the door.
 */
void open_door();

/**
 * @brief closes the door.
 */
void close_door();

#endif