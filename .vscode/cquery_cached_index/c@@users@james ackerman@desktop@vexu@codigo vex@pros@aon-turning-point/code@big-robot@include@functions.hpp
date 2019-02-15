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



#endif /* end of include guard:  */
