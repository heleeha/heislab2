/**
 * @file
 * @brief Module for holding the door.
 *
 *
 * Pauline M. Jonassen & Helene E. Haugen
 */
#include <time.h>

/**
 * @brief check is begin is grater then 2.
 * @return 0 if @p diff_sec is bigger then 2 and otherwise returns 1.
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
 * @brief Checks if the stopbutton is pushed, if so stop the elevator.
 */
void set_emergency_stop();

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