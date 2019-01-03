//Definitions of all constants used in project

#ifndef definitions_hpp
#define definitions_hpp
//#pragma once //TODO: test this to see if it works without having to use ifndef etc.

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

//For Driver Control height buttons
//TODO: Find actual low and high goal values in degrees (TUNING)
const int STARTING_HEIGHT = 0;
const int LOW_GOAL_HEIGHT = 53;   //low goal is 69% of high goal more or less but this is in degrees so idk
const int HIGH_GOAL_HEIGHT = 75;








#endif /* end of include guard:  */
