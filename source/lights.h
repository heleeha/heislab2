/**
 * @file
 * @brief Module for lights.
 *
 *
 * Pauline M. Jonassen & Helene E. Haugen
 */



/**
 * @brief checks if any order buttons have been pushed and turns on the light in the pushed button
 */
void set_order_light_on();

/**
 * @brief checks floor sensors and turns on the floor indicator light, the light switches when another floor sensor is active 
 */
void set_floor_light();

/**
 * @brief checks if the stop button is pushed, and turns on the light in the stop button if so
 */
void set_stop_light();

/**
 * @brief turns off order light if the elevator is in right floor
 */
void set_order_light_off();

/**
 * @brief turns off all order lights
 */
 void clear_all_order_lights();

/**
 * @brief turns off all order lights
 */
 void clear_stop_light();
