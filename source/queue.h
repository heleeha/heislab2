
/**
 * @file
 * @brief Module for queue.
 *
 *
 * Pauline M. Jonassen & Helene E. Haugen
 */

/**
 * @brief Array for inside queue, with @p HARDWARE_NUMBER_OF_FLOORS elements.
 */
int inside_queue[HARDWARE_NUMBER_OF_FLOORS];

/**
 * @brief Array for down queue, with @p HARDWARE_NUMBER_OF_FLOORS elements.
 */
int down_queue[HARDWARE_NUMBER_OF_FLOORS];

/**
 * @brief Array for the up queue with @p HARDWARE_NUMBER_OF_FLOORS elements.
 */
int up_queue[HARDWARE_NUMBER_OF_FLOORS];


/**
 * @brief function which are checking if any buttons are pushed at, if so it sets the right element in the right queue to 1.
 */
void add_to_queue();

/**
 * @brief function checking which floor you are in. If there are any orders at current floor, the right element in the right floor is set to 0.
 */
void delete_order();


/**
 * @brief function setting every element in every queue to 0.
 */
void delete_all_orders();



