/**
 * @file
 * @brief Driver for controlling the motor with PID regulation
 */

#ifndef PID_H_
#define PID_H_


/**
 * @brief PID controller that controls the motor based on its position
 */
void PID_controller(void);

/**
 * @brief Initializes the PID controller and its sampling period of the motor position
 */
void PID_init(void);


/**
 * @brief Sets the position reference by reading the left slider input
 */
void PID_set_ref(void);


/**
 * @brief Resets the PID controller and the caLculated errors in position
 */
void PID_reset(void);


/**
 * @brief Sets the parameters used in the PID controller
 * @param kp_inv The Kp parameter for the controller is set as Kp = Kp / @p kp_inv 
 * @param ki The Ki parameter is used for deciding how much effect the integral action has
 * @param kd The kd parameter is used for deciding how much effect the derivative action has
 */
void PID_set_parameters(int kp_inv, int ki, int kd);


#endif /* PID_H_ */