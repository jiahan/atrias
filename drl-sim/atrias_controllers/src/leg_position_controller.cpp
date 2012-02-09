#include <atrias_controllers/controller.h>

#define DELTA_Y (0.5*sin(input->leg_angleB) + 0.5*sin(input->leg_angleA))
#define DELTA_X (-0.5*cos(input->leg_angleB) - 0.5*cos(input->leg_angleA))
#define LEG_LENGTH sqrt(DELTA_Y*DELTA_Y + DELTA_X*DELTA_X)

#define Lab 0.15557

extern void initialize_leg_position_controller(ControllerInput* input, ControllerOutput* output, ControllerState* state, 
	ControllerData *data)
{
	output->motor_torqueA = 0.;
	output->motor_torqueB = 0.;
	output->motor_torque_hip = 0.;
	LEG_POS_CONTROLLER_STATE(state)->prev_angle = 0;
}


extern void update_leg_position_controller(ControllerInput* input, ControllerOutput* output, ControllerState* state, ControllerData *data)
{
	float des_mtr_angA = LEG_POS_CONTROLLER_DATA(data)->leg_ang - PI + acos( LEG_POS_CONTROLLER_DATA(data)->leg_len );
	float des_mtr_angB = LEG_POS_CONTROLLER_DATA(data)->leg_ang + PI - acos( LEG_POS_CONTROLLER_DATA(data)->leg_len );
	float des_hip_ang = 0.99366*input->body_angle + 0.03705;

	if ((des_hip_ang < -0.2007) || (des_hip_ang > 0.148))
		des_hip_ang = input->body_angle;

	output->motor_torqueA = LEG_POS_CONTROLLER_DATA(data)->p_gain * (des_mtr_angA - input->motor_angleA) 
		- LEG_POS_CONTROLLER_DATA(data)->d_gain * input->motor_velocityA;
	output->motor_torqueB = LEG_POS_CONTROLLER_DATA(data)->p_gain * (des_mtr_angB - input->motor_angleB) 
		- LEG_POS_CONTROLLER_DATA(data)->d_gain * input->motor_velocityB;

	output->motor_torque_hip = LEG_POS_CONTROLLER_DATA(data)->hip_p_gain * (des_hip_ang - input->hip_angle)
		- LEG_POS_CONTROLLER_DATA(data)->hip_d_gain * input->hip_angle_vel;

	

//	printk("                                                                                              %d\n",(int)((des_hip_ang)*1000));
}


extern void takedown_leg_position_controller(ControllerInput* input, ControllerOutput* output, ControllerState* state, ControllerData *data)
{
	output->motor_torqueA = output->motor_torqueB = 0.;
}
