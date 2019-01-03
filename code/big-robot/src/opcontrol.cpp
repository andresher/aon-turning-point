#include "main.h"
#include "okapi/api.hpp"
#include "definitions.hpp"

 using namespace okapi;

//Better button names
//TODO: check syntax for ControllerButton for R1/R2/L1/L2/Down/left/right buttons
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
     //Assuming controller values reset to 0 after every use
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
