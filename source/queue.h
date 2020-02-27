
/**
 * @file
 * @brief Module for queue.
 *
 *
 * Pauline M. Jonassen & Helene E. Haugen
 */

#ifndef QUEUE_H
#define QUEUE_H
/**
 * @brief checking if there are any orders at current floor.
 * @return 1 if there are orders at current floor, return 0 otherwise.
 */
int check_order_at_current_floor();

/**
 * @brief checking if there are any orders at @p last_floor.
 * @param[in] last_floor 
 * @return 1 if there are orders at last floor, return 0 otherwise.
 */
int order_at_last_floor(int last_floor);

/**
 * @brief checking if there are any orders.
 * @return 1 if there are any orders, return 0 otherwise.
 */
int order_in_queues();

/**
 * @brief function which checks if any buttons are pushed, if so it sets the right element in the right queue to 1.
 */
void add_to_queue();

/**
 * @brief If there are any orders at @p last_floor, the right element in the right queue is set to 0.
 * @param[in] last_floor 
 */
void delete_order(int last_floor);


/**
 * @brief function setting every element in every queue to 0.
 */
void delete_all_orders();

/**
 * @brief function returning current floor.
 * @return the floor number or -1 if the elevator is between floors. 
 */
int current_floor();

/**
 * @brief function which takes in a pointer @p *p_last_floor, and updates it to the last floor the elevator was at.
 * @param[out] p_last_floor pointer to last_floor
 */

void update_last_floor(int* p_last_floor);

/**
 * @brief function which uses @p lastfloor to check if there are orders above it.
 * @param[in] last_floor 
 * @return 1 if there is orders above or 0 if not.
 */
int check_order_above(int last_floor);

/**
 * @brief function which uses @p lastfloor to check if there are orders below it.
 * @param[in] last_floor 
 * @return 1 if there is orders below or 0 if not.
 */
int check_order_below(int last_floor);

/**
 * @brief function which checks if the up button at current floor is pushed, and takes in a pointer @p *p_last_floor and updates it.
 * @param[out] p_last_floor pointer to last_floor
 * @return 1 if the up button at current floor is pushed or 0 if not.
 */
int up_button_at_current_floor(int *p_last_floor);

/**
 * @brief function which checks if the down button at current floor is pushed, and takes in a pointer @p *p_last_floor and updates it.
 * @param[out] p_last_floor pointer to last_floor
 * @return 1 if the down button at current floor is pushed or 0 if not.
*/
int down_button_at_current_floor(int *p_last_floor);

/**
 * @brief function which checks if the cab button at current floor is pushed, and takes in a pointer @p *p_last_floor and updates it.
 * @param[out] p_last_floor pointer to last_floor
 * @return 1 if the cab button at current floor is pushed or 0 if not.
 */
int cab_button_at_current_floor(int *p_last_floor);

#endif