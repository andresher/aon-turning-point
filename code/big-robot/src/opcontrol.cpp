#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

 using namespace okapi;

 // Chassis definition
 // Assume this is correct for now
 // TODO: Update with the real robot values
 const int DRIVE_MOTOR_LEFT_1 = 1;   //FMB = Front, Middle, Back
 const int DRIVE_MOTOR_LEFT_2 = 2;
 const int DRIVE_MOTOR_LEFT_3 = 3;
 const int DRIVE_MOTOR_RIGHT_1 = 4;
 const int DRIVE_MOTOR_RIGHT_2 = 5;
 const int DRIVE_MOTOR_RIGHT_3 = 6;
 const auto WHEEL_DIAMETER = 4_in;
 const auto CHASSIS_WIDTH = 15.23_in;

 // Lift definition
 // Assume this is correct for now
 // TODO: Update with the real robot values
 const double liftkP = 1.0;
 const double liftkI = 0.001;
 const double liftkD = 0.1;
 const int LIFT_MOTOR_RIGHT = 7;
 const int LIFT_MOTOR_LEFT = 8;

 // Intake definition
 // Assume this is correct for now
 // TODO: Update with the real robot values
 const int INTAKE_MOTOR_RIGTH_1 = 9;    // 1 for side roller
 const int INTAKE_MOTOR_RIGTH_2 = 10;   // 2 for rotator
 const int INTAKE_MOTOR_LEFT_1 = 11;
 const int INTAKE_MOTOR_LEFT_2 = 12;

 // Puncher definition
 // Assume this is correct for now
 // TODO: Update with the real robot values
 const int PUNCHER_MOTOR_1 = 13;
 const int PUNCHER_MOTOR_2 = 14;

 // Conveyor definition
 // Assume this is correct for now
 // TODO: Update with the real robot values
 const int CONVEYOR_MOTOR = 15;

 // Controller object creation
 auto driveController = ChassisControllerFactory::create(
   {DRIVE_MOTOR_LEFT_1, DRIVE_MOTOR_LEFT_2, DRIVE_MOTOR_LEFT_3},
   {DRIVE_MOTOR_RIGHT_1, DRIVE_MOTOR_RIGHT_2, DRIVE_MOTOR_RIGHT_3},
   AbstractMotor::gearset::green,
   {WHEEL_DIAMETER, CHASSIS_WIDTH}
 );
 auto liftController = AsyncControllerFactory::posPID(
   {LIFT_MOTOR_RIGTH, LIFT_MOTOR_LEFT},
   liftkP, liftkI, liftkD
 );
 auto intakeController = AsyncControllerFactory::velIntegrated(
   {INTAKE_MOTOR_RIGTH_1,
   INTAKE_MOTOR_RIGTH_2,
   INTAKE_MOTOR_LEFT_1,
   INTAKE_MOTOR_LEFT_2}
 );
 auto puncherController = AsyncControllerFactory::posIntegrated(
   {PUNCHER_MOTOR_1, PUNCHER_MOTOR_2}
 );
 auto conveyorController = AsyncControllerFactory::velIntegrated(CONVEYOR_MOTOR);

//For Driver Control height buttons
//TO DO: Find actual low and high goal values
//NOTE: I assume these values aren't to scale (not in m, cm, inches, etc.)
const int HEIGHTS = 2;
const int LOW_GOAL_HEIGHT = 50
const int HIGH_GOAL_HEIGHT = 75

///////////////////////////////OPCONTROL///////////////////////////////

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);
	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		right_mtr = right;
		pros::delay(20);
	}
}