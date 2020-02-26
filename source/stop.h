/**
 * @file
 * @brief Module for timer, stop and motor direction.
 *
 *
 * Pauline M. Jonassen & Helene E. Haugen
 */
#include <time.h>

/**
 * @brief checks if begin is grater than 2.
 * @return 0 if @p diff_sec is bigger than 2 and otherwise returns 1.
 */
int counting_3seconds();

/**
 * @brief returns the starttime. 
 * @return starttime which is a clock_t.
 */
clock_t get_start_time();

/**
 * @brief sets @p start to the current clocktime.
 */
void set_start_time();

/**
 * @brief Checks if the stopbutton is pushed, if so stops the elevator.
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