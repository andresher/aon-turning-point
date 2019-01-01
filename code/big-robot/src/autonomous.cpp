#include "main.h"
#include "okapi/api.hpp"

 using namespace okapi;



 // Chassis definition
 // Assume this is correct for now
 // TODO: Update with the real robot values
 const int DRIVE_MOTOR_LEFT_1 = 1;   //1,2,3 = Front, Middle, Back
 const int DRIVE_MOTOR_LEFT_2 = 2;
 const int DRIVE_MOTOR_LEFT_3 = 3;
 const int DRIVE_MOTOR_RIGHT_1 = 4;  //1,2,3 = Front, Middle, Back
 const int DRIVE_MOTOR_RIGHT_2 = 5;
 const int DRIVE_MOTOR_RIGHT_3 = 6;
 const int DRIVE_PNEUMATIC = 1;     //port A //change to A if this doesn't work
 const auto WHEEL_DIAMETER = 4_in;
 const auto CHASSIS_WIDTH = 15.24_in;


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
 const double flipkP = 1.0;
 const double flipkI = 0.001;
 const double flipkD = 0.1;
 const int INTAKE_MOTOR_RIGHT = 9;    // 1 for side roller
 const int ROTATOR_MOTOR_RIGHT = 10;   // 2 for rotator
 const int INTAKE_MOTOR_LEFT = 11;
 const int ROTATOR_MOTOR_LEFT = 12;

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
 //TODO: Reverse motors that need to be reversed
 auto driveController = ChassisControllerFactory::create(
   {DRIVE_MOTOR_LEFT_1, DRIVE_MOTOR_LEFT_2, DRIVE_MOTOR_LEFT_3},
   {DRIVE_MOTOR_RIGHT_1, DRIVE_MOTOR_RIGHT_2, DRIVE_MOTOR_RIGHT_3},
   AbstractMotor::gearset::green,
   {WHEEL_DIAMETER, CHASSIS_WIDTH}
 );
 auto liftController = AsyncControllerFactory::posPID(
   {LIFT_MOTOR_RIGHT, LIFT_MOTOR_LEFT},
   liftkP, liftkI, liftkD
 );
 auto intakeController = AsyncControllerFactory::velIntegrated(
   {INTAKE_MOTOR_RIGHT,INTAKE_MOTOR_LEFT}
 );
 auto rotatorController = AsyncControllerFactory::posPID(
	{ROTATOR_MOTOR_RIGHT,ROTATOR_MOTOR_LEFT}
  flipkP, flipkI, flipkD
 );
 auto puncherController = AsyncControllerFactory::posIntegrated(
   {PUNCHER_MOTOR_1, PUNCHER_MOTOR_2}
 );
 auto conveyorController = AsyncControllerFactory::velIntegrated(CONVEYOR_MOTOR);


// Write autonomous code here
//TODO: measure degrees needed for 1 "punch" of puncher, probably 300-360 or so
//TODO: line tracker code task running continuously
//TODO: Vision Sensor code
//TODO: Find out how to reverse motors I doubt the controllers can do this automatically for non-chassis controllers
//TODO: Verify clockwise and counter-clockwise syntax for okapi motor controllers
//TODO: Chekc if lift maintains its height when raised
//TODO: Verify if these controller values are accumulative or they reset to 0 after every use
////////////////////////////////////AUTONOMOUS///////////////////////////////////////////////////
//TODO: Find actual low and high goal values in degrees (TUNING)
const int STARTING_HEIGHT = 0;
const int LOW_GOAL_HEIGHT = 53;   //low goal is 69% of high goal more or less but this is in degrees so idk
const int HIGH_GOAL_HEIGHT = 75;
void autonomous() {

  //Assuming controller values reset to 0 after every use
  //Autonomous routine for 24x24 RED
  puncherController.setTarget(300_deg);       //Shoot ball to top center flag
  puncherController.waitUntilSettled();
  driveController.turnAngle(35_deg);         //Turn towards same color cap //I assume this is clockwise
  driveController.waitUntilSettled();
  intakeController.setTarget(200_rpm);        //Chupa intake
  conveyorController.setTarget(200_rpm);      //Sube bola al puncher
  driveController.moveDistance(4_ft);         //Move towards same color cap
  driveController.waitUntilSettled();
  pros::delay(600);                          //Wait for robot to intake ball and cap securely
  intakeController.setTarget(30_rpm);         //Use intake to hold cap
  //TODO: REPLACE THIS TURN WITH VISION SENSOR CODE
  driveController.turnAngle(-80_deg);          //Turn facing middle center flag //I assume this is clockwise
  puncherController.setTarget(300_deg);       //Shoot ball to middle center flag
  puncherController.waitUntilSettled();
  liftController.setTarget(LOW_GOAL_HEIGHT);  //Raise lift to low goal height
  driveController.turnAngle(80_deg);         //Turn clockwise face opposite team's side
  puncherController.waitUntilSettled();
  driveController.moveDistance(-2_ft);        //move backwards until "horizontally" alligned with back low goal post
  driveController.waitUntilSettled();
  driveController.turnAngle(80_deg);         //Turn clockwise to face back low goal
  driveController.moveDistance(1_ft);         //Drive towards back low goal
  pros::delay(300)                            //wait for robot to stop jiggling
  liftController.setTarget(-10_deg);  //Raise lower lift to insert cap on post
  intakeController.setTarget(-100_rpm);       //Reverse intake to release cap
  driveController.moveDistance(-0.5_ft);      //Drive in reverse away from cap on goal
  driveController.waitUntilSettled();
  intakeController.setTarget(0_rpm);
  liftController.setTarget(-(LOW_GOAL_HEIGHT-10));  //Return lift to starting position
  driveController.turnAngle(-90_deg);          //Turn 90 degrees counter-clockwise to face opponent-colored cap
  driveController.waitUntilSettled();
  intakeController.setTarget(200_rpm);        //Chupa intake
  conveyorController.setTarget(200_rpm);      //Sube bola al puncher
  driveController.moveDistance(4_ft);         //Move towards same color cap
  driveController.waitUntilSettled();
  pros::delay(600);                           //Wait for robot to intake ball and cap securely
  intakeController.setTarget(30_rpm);         //Use intake to hold cap
  liftController.setTarget(LOW_GOAL_HEIGHT);  //Raise lift to low goal height
  driveController.turnAngle(-120_deg);         //Turn clockwise face opposite team's side
  puncherController.waitUntilSettled();
  rotatorController.setTarget(180_deg);       //Flip cap
  driveController.setTarget(115_deg);         //Turn 115 degrees clockwise towards side low goal








  //maintain lift at height


  //
  // Motor intakeL(INTAKE_MOTOR_LEFT);        //motor on INTAKE_MOTOR_LEFT port
  // Motor intakeR(INTAKE_MOTOR_RIGHT, true); //motor on INTAKE_MOTOR_RIGHT port reversed driection
  // Motor conveyor(CONVEYOR_MOTOR);          //motor on CONVEYOR_MOTOR port
  // Motor puncher1(PUNCHER_MOTOR_1);         //motor on PUNCHER_MOTOR_1 port
  // Motor puncher2(PUNCHER_MOTOR_2, true);   //motor on PUNCHER_MOTOR_2 port
  //
  // IntakeR.move_voltage(-127);
  //
  // state != state;
  // sensor.set_value(state);
  //
  // rotatorController.setTarget(180_deg);  //flip intake
  // conveyorController.setTarget(200_rpm); //move conveyor full speed
  // liftController.setTarget(50_deg);      //raise lift //TODO: measure distance per degree
  // driveController.moveDistance(1_m);     // Move 1 meter to the first goal
  // driveController.turnAngle(90_deg);     // Turn 90 degrees
  //pros::delay(1000) or pros::Task::delay(1000) idk which one
}
