#include "main.h"
#include "okapi/api.hpp"

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

using namespace okapi;

// Chassis definition
// Assume this is correct for now
// TODO: Update with the real robot values
const int DRIVE_MOTOR_LEFT_1 = 1;
const int DRIVE_MOTOR_LEFT_2 = 2;
const int DRIVE_MOTOR_LEFT_3 = 3;
const int DRIVE_MOTOR_RIGHT_1 = 4;
const int DRIVE_MOTOR_RIGHT_2 = 5;
const int DRIVE_MOTOR_RIGHT_3 = 6;
const auto WHEEL_DIAMETER = 4_in;
const auto CHASSIS_WIDTH = 13.5_in;

// Lift definition
// Assume this is correct for now
// TODO: Update with the real robot values
const double liftkP = 1.0;
const double liftkI = 0.001;
const double liftkD = 0.1;
const int LIFT_MOTOR = 7;

// Cap Intake definition
// Assume this is correct for now
// TODO: Update with the real robot values
const int CAP_INTAKE_MOTOR = 8;

// Shooter definition
// Assume this is correct for now
// TODO: Update with the real robot values
const int SHOOTER_MOTOR_1 = 9;
const int SHOOTER_MOTOR_2 = 10;

// Ball Intake definition
// Assume this is correct for now
// TODO: Update with the real robot values
const int BALL_INTAKE_MOTOR = 11;

// Ball Indexer definition
// Assume this is correct for now
// TODO: Update with the real robot values
const int BALL_INDEXER_MOTOR = 12;

// Controller object creation
auto driveController = ChassisControllerFactory::create(
  {DRIVE_MOTOR_LEFT_1, DRIVE_MOTOR_LEFT_2, DRIVE_MOTOR_LEFT_3},
  {DRIVE_MOTOR_RIGHT_1, DRIVE_MOTOR_RIGHT_2, DRIVE_MOTOR_RIGHT_3},
  AbstractMotor::gearset::green,
  {WHEEL_DIAMETER, CHASSIS_WIDTH}
);
auto liftController = AsyncControllerFactory::posPID(
  LIFT_MOTOR,
  liftkP, liftkI, liftkD
);
auto capIntakeController = AsyncControllerFactory::velIntegrated(CAP_INTAKE_MOTOR);
auto shooterController = AsyncControllerFactory::velIntegrated(
  {SHOOTER_MOTOR_1, SHOOTER_MOTOR_2}
);
auto ballIntakeController = AsyncControllerFactory::velIntegrated(BALL_INTAKE_MOTOR);
auto ballIndexerController = AsyncControllerFactory::velIntegrated(BALL_INDEXER_MOTOR);

// Write autonomous code here
void autonomous() {}
