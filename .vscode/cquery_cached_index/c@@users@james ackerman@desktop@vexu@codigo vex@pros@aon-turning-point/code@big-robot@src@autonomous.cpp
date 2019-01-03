#include "main.h"
#include "okapi/api.hpp"
#include "definitions.hpp"

 using namespace okapi;

 /**
  * Runs the user autonomous code. This function will be started in its own task
  * with the default priority and stack size whenever the robot is enabled via
  * the Field Management System or the VEX Competition Switch in the autonomous
  * mode. Alternatively, this function may be called in initialize or opcontrol
  * for non-competition testing purposes.
  *
  * If the robot is disabled or communications is lost, the autonomous task
  * will be stopped. Re-enabling the robot will restart the task, not re-start it
  * from where it left off.
  */

// Write autonomous code here
//TODO: verify if you can use non-async functions with async controllers, if not, fix code
//TODO: try and place all the motor definitions and stuff in
//TODO: measure degrees needed for 1 "punch" of puncher, probably 300-360 or so
//TODO: line tracker code task running continuously
//TODO: Vision Sensor code
//TODO: Find out how to reverse motors I doubt the controllers can do this automatically for non-chassis controllers
//TODO: Verify clockwise and counter-clockwise syntax for okapi motor controllers
//TODO: Chekc if lift maintains its height when raised
//TODO: Verify if these controller values are accumulative or they reset to 0 after every use

//TODO: Find actual low and high goal values in degrees (TUNING)
const int STARTING_HEIGHT = 0;
const int LOW_GOAL_HEIGHT = 53;   //low goal is 69% of high goal more or less but this is in degrees so idk
const int HIGH_GOAL_HEIGHT = 75;
////////////////////////////////////AUTONOMOUS///////////////////////////////////////////////////
void autonomous() {

  //Assuming controller values reset to 0 after every use
  //Autonomous routine for 24x24 RED
  //PART 1: SHOOT PRELOAD AND BALL, SCORE BACK LOW GOAL CAP
  puncherController.setTarget(300_deg);       //Shoot ball to top center flag
  puncherController.waitUntilSettled();
  driveController.turnAngle(35_deg);          //Turn towards same color cap //I assume this is clockwise
  driveController.waitUntilSettled();
  intakeController.setTarget(200_rpm);        //Chupa intake
  conveyorController.setTarget(200_rpm);      //Sube bola al puncher
  driveController.moveDistanceAsync(4_ft);    //Move towards same color cap
  driveController.waitUntilSettled();
  pros::delay(600);                           //Wait for robot to intake ball and cap securely
  intakeController.setTarget(30_rpm);         //Use intake to hold cap
  //TODO: REPLACE THIS TURN WITH VISION SENSOR CODE
  driveController.turnAngle(-80_deg);         //Turn facing middle center flag //I assume this is clockwise
  puncherController.setTarget(300_deg);       //Shoot ball to middle center flag
  puncherController.waitUntilSettled();
  liftController.setTarget(LOW_GOAL_HEIGHT);  //Raise lift to low goal height
  driveController.turnAngle(80_deg);          //Turn clockwise face opposite team's side
  puncherController.waitUntilSettled();
  driveController.moveDistanceAsync(-2_ft);   //move backwards until "horizontally" alligned with back low goal post
  driveController.waitUntilSettled();
  driveController.turnAngle(80_deg);          //Turn clockwise to face back low goal
  driveController.moveDistanceAsync(1_ft);    //Drive towards back low goal
  pros::delay(300);                           //wait for robot to stop jiggling
  liftController.setTarget(-10_deg);          //Raise lower lift to insert cap on post
  intakeController.setTarget(-100_rpm);       //Reverse intake to release cap
  driveController.moveDistanceAsync(-0.5_ft); //Drive in reverse away from cap on goal
  driveController.waitUntilSettled();
  intakeController.setTarget(0_rpm);
  liftController.setTarget(-(LOW_GOAL_HEIGHT-10));  //Return lift to starting position

  //PART 2: SCORE CAP ON SIDE LOW GOAL

  driveController.turnAngle(-90_deg);         //Turn 90 degrees counter-clockwise to face opponent-colored cap
  intakeController.setTarget(200_rpm);        //Chupa intake
  conveyorController.setTarget(200_rpm);      //Sube bola al puncher
  driveController.moveDistanceAsync(4_ft);    //Move towards same color cap
  driveController.waitUntilSettled();
  pros::delay(600);                           //Wait for robot to intake ball and cap securely
  intakeController.setTarget(30_rpm);         //Use intake to hold cap
  //maintain lift at height
  liftController.setTarget(LOW_GOAL_HEIGHT);  //Raise lift to low goal height
  rotatorController.setTarget(180_deg);       //Flip cap
  driveController.setTarget(-110_deg);        //Turn 110 degrees counter-clockwise towards slightly ahead of side low goal
  driveController.moveDistanceAsync();        //Drive forwards towards slightly ahead of side low goal
  driveController.setTarget(10_deg);          //Turn 10 degrees counter-clockwise to face side low goal
  driveController.moveDistanceAsync(0.5_ft);  //Drive towards back low goal
  pros::delay(300);                           //give robot some time to move
  liftController.setTarget(-10_deg);          //Raise lower lift to insert cap on post
  intakeController.setTarget(-100_rpm);       //Reverse intake to release cap
  driveController.moveDistanceAsync(-0.5_ft); //Drive in reverse away from cap on goal
  driveController.waitUntilSettled();
  intakeController.setTarget(0_rpm);
  liftController.setTarget(-(LOW_GOAL_HEIGHT-10));  //Return lift to starting position

  //PART 3: SCORE CAP BROUGHT BY 15X15 ON HIGH GOAL

  driveController.turnAngle(90_deg);           //Turn 90 degrees clockwise to face cap left by 15x15 robot
  driveController.waitUntilSettled();
  intakeController.setTarget(200_rpm);         //Chupa intake
  driveController.moveDistanceAsync(4.5_ft);   //Move towards cap left by 15x15 robot
  driveController.waitUntilSettled();
  pros::delay(600);                            //Wait for robot to intake ball and cap securely
  intakeController.setTarget(30_rpm);          //Use intake to hold cap
  liftController.setTarget(HIGH_GOAL_HEIGHT);  //raise lift to high goal height
  //Maybe use line trackers here?
  driveController.moveDistanceAsync(-0.5_ft);  //drive backwards to allign center of robot with white line with white line
  driveController.waitUntilSettled();
  driveController.turnAngle(-90_deg);          //Turn 90 degrees counter-clockwise to face high goal post
  driveController.moveDistanceAsync(0.5_ft);  //Drive towards back low goal
  pros::delay(300);                           //give robot some time to move
  liftController.setTarget(-10_deg);          //Raise lower lift to insert cap on post
  intakeController.setTarget(-100_rpm);       //Reverse intake to release cap
  driveController.moveDistanceAsync(-0.5_ft); //Drive in reverse away from cap on goal
  driveController.waitUntilSettled();
  intakeController.setTarget(0_rpm);
  liftController.setTarget(-(HIGH_GOAL_HEIGHT-10));  //Return lift to starting position

  //PART 4: RETURN TO BACK OF FIELD
  driveController.turnAngle(70_deg);           //Turn robot on an angle so it can cut to the back of the field
  driveController.moveDistanceAsync(-6_ft);   //Drive in reverse away from cap on goal
  driveController.waitUntilSettled();

  //reference stuff
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
  // driveController.moveDistanceAsync(1_m);     // Move 1 meter to the first goal
  // driveController.turnAngle(90_deg);     // Turn 90 degrees
  //pros::delay(1000) or pros::Task::delay(1000) idk which one
}
