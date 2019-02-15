#ifndef auton_functions_hpp
#define auton_functions_hpp

#include "main.h"
#include "okapi/api.hpp"
#include "definitions.hpp"

void place_cap(int height)
  {
    liftController.setTarget(-10_deg);          //Raise lift to insert cap on post
    intakeController.setTarget(-100_rpm);       //Reverse intake to release cap
    driveController.moveDistanceAsync(-0.5_ft); //Drive in reverse away from cap on goal
    driveController.waitUntilSettled();
    intakeController.setTarget(0_rpm);
    liftController.setTarget(-(height-10));  //Return lift to starting position
  }
//
// void line_allign_front()
// {
//
//   while(linetrackerL.getvalue() > 900 && linetrackerR.getvalue() > 900)
// 	{
//     driveController.move_voltage(80)   //drive forward if line has not been reached
//   }
// 	if(linetrackerR.getvalue() > 900 < 900)
// 	{
//       //TODO: Change to PROS  sytax for mototrs
// 		while(linetrackerL.getvalue() > 900)
// 		{
// 				motor[port2] = 10;  //40
// 				motor[port4] = 10;
// 				motor[port6] = -30;  //30
// 				motor[port8] = -30;
// 		}
// 	}
// 		else if(linetrackerL.getvalue() < 900)
// 		{
// 			while(linetrackerR.getvalue() > 900)
// 			{
// 				motor[port2] = -30;  //40
// 				motor[port4] = -30;
// 				motor[port6] =	10;  //30
// 				motor[port8] =	10;
// 			}
// 		}
// 	motor[port2] = 0;
// 	motor[port4] = 0;
// 	motor[port6] = 0;
// 	motor[port8] = 0;
// }

}


#endif /* end of include guard:  */
