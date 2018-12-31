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
//TO DO: Find actual low and high goal values in degrees (TUNING)
const int STARTING_HEIGHT = 0;
const int LOW_GOAL_HEIGHT = 53;   //low goal is 69% of high goal more or less but this is in degrees so idk
const int HIGH_GOAL_HEIGHT = 75;

//Better button names
ControllerButton RightBumperUP(ControllerDigital::R1);
ControllerButton RightBumperDOWN(ControllerDigital::R2);
ControllerButton LeftBumperUP(ControllerDigital::L1);
ControllerButton LeftBumperDOWN(ControllerDigital::L2);
ControllerButton ButtonA(ControllerDigital::A);
ControllerButton ButtonB(ControllerDigital::B);
ControllerButton ButtonX(ControllerDigital::X);
ControllerButton ButtonY(ControllerDigital::Y);
ControllerButton ButtonDOWN(ControllerDigital::DOWN);
ControllerButton ButtonLEFT(ControllerDigital::LEFT);
ControllerButton ButtonRIGHT(ControllerDigital::RIGHT);

////////////////////////////////////OPCONTROL///////////////////////////////////////////////////
void opcontrol() {
  Controller controller;
  //use _mtr syntax if the following doesnt work
  //example: Motor intaker = INTAKE_MOTOR_LEFT_rmtr     <- reversed motor on INTAKE_MOTOR_LEFT port
  Motor intakeL(INTAKE_MOTOR_LEFT);        //motor on INTAKE_MOTOR_LEFT port
  Motor intakeR(INTAKE_MOTOR_RIGHT, true); //motor on INTAKE_MOTOR_RIGHT port reversed driection
  Motor conveyor(CONVEYOR_MOTOR);          //motor on CONVEYOR_MOTOR port
  Motor puncher1(PUNCHER_MOTOR_1);         //motor on PUNCHER_MOTOR_1 port
  Motor puncher2(PUNCHER_MOTOR_2, true);   //motor on PUNCHER_MOTOR_2 port
  int CURRENT_HEIGHT = 0;                  //For Lift
  bool state = LOW;                        //For Pneumatics //Change to false if this doesn't not work
  pros::ADIDigitalOut piston (DRIVE_PNEUMATIC); //piston on DRIVE_PNEUMATIC port

  while (true)
	{
		 //////////////////////////////CHASSIS(DRIVE)///////////////////////////////
	 	 //Arcade drive FW-BW on Left Y axis turns on Right X
		 drive.arcade(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightX));
     //////////////////////////////TRANSMISSION/////////////////////////////////
     if (ButtonRIGHT.changedToPressed())
     {
         state != state;
         sensor.set_value(state);
     }
     /////////////////////////////////INTAKE////////////////////////////////////
     //using straight up move commands instead of okapilib
     //how to use target for okapilib velPID? rpm? 0-100? 0-127?
     if (RightBumperUP.isPressed())          //Hold button to Chupa Intake
     {
         IntakeL.move_voltage(127);
         IntakeR.move_voltage(127);
     }
     else if (RightBumperDOWN.isPressed())  //Hold button to Bota Intake
     {
         intakeL.move_voltage(-127);
         IntakeR.move_voltage(-127);
     }
     else                                   //Intake stops if nothing is pressed
     {
         intakeL.move_voltage(0);
         IntakeR.move_voltage(0);
     }
     ///////////////////////////////CONVEYOR////////////////////////////////////
     //using straight up move commands instead of okapilib
     //how to use target for okapilib velPID? rpm? 0-100? 0-127?
     if (LeftBumperUP.isPressed())
     {
         conveyor.move_voltage(127);
     }
     else if (LeftBumperUP.isPressed())
     {
         conveyor.move_voltage(-127);
     }
     else
     {
         conveyor.move_voltage(0);
     }
		 /////////////////////////////INTAKE ROTATOR////////////////////////////////
		 if (ButtonDOWN.changedToPressed())      //Press button to flip intake
		 {
			 rotatorController.setTarget(180);
		 }
     ////////////////////////////////PUNCHER////////////////////////////////////
     if (ButtonLEFT.isPressed())             //Hold Button to fire puncher
     {
         puncher1.move_voltage(127);
         puncher2.move_voltage(127);
     }
     else
     {
         puncher1.move_voltage(0);
         puncher2.move_voltage(0);
     }
		 /////////////////////////////////LIFT//////////////////////////////////////
     if (ButtonA.changedToPressed())      //Press button to go to raise lift to height
		 {
       liftController.setTarget(STARTING_HEIGHT-CURRENT_HEIGHT);
       CURRENT_HEIGHT = STARTING_HEIGHT;
     }
		 else if (ButtonB.changedToPressed())
		 {
       liftController.setTarget(LOW_GOAL_HEIGHT-CURRENT_HEIGHT);
       CURRENT_HEIGHT = LOW_GOAL_HEIGHT;
     }
		else if (ButtonX.changedToPressed())
	 	 {
			 liftController.setTarget(HIGH_GOAL_HEIGHT-CURRENT_HEIGHT);
       CURRENT_HEIGHT = HIGH_GOAL_HEIGHT;
		 }

		 pros::delay(20)
	 }
}
