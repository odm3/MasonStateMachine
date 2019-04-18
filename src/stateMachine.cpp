#include "main.h"
#include "hardware.h"
#include "stateMachine.h"
#include "deviceDefinitions.h"


////////////////////////////// BOOLEAN STATES////////////////////////////////
bool isIntakeIn = false;
bool isIntakeOut = false;

bool isAngleHigh = true;
bool isAngleLow = false;
bool isHookOut = false;
bool Shoot = false;

//////////////////////////////////////////////////////////////////////////////
////////////////////////////// INTAKE FUNCTIONS //////////////////////////
void intakeIn( )
{
    LowerIntakeSpeed = 127;
    UpperIntakeSpeed = 127;
    isIntakeIn = true;
    isIntakeOut = false;
}
void intakeOut( )
{
    LowerIntakeSpeed = -127;
    UpperIntakeSpeed = -127;
    isIntakeIn = false;
    isIntakeOut = true;
}
void intakestop( )
{
    LowerIntakeSpeed = 0;
    UpperIntakeSpeed = 0;
    isIntakeIn = false;
    isIntakeOut = false;
}
//////////////////////////////////////////////////////////////////////////////
////////////////////////////// ANGLE ADJUST FUNCTIONS ////////////////////


pros::Task startAngleAdjustHi (launchAdjustHi, NULL, TASK_PRIORITY_DEFAULT,
                                TASK_STACK_DEPTH_DEFAULT,"ANGLE HIGH GO!");
void launchAdjustHi( void * param)
{
    //int HighAngle = arcsin(sqrt(highHeight*highHeight+Xdistance*Xdistance)/highHeight);
  while( startAngleAdjustHi.notify_take(true, TIMEOUT_MAX))
  {
      double angleP = -.30;
      int targetPositionAngle = 3500;// HighAngle;
      int error = targetPositionAngle - launchAdjustAngle;
      double timeInit = pros::millis();
      double timechange;
      while(abs( error ) > 50 )
      {
        error = targetPositionAngle - launchAdjustAngle;
        timechange = pros::millis() - timeInit;
        launchAdjust = ( angleP * error );
      }
      launchAdjust = launcherAdjuster.set_brake_mode(MOTOR_BRAKE_HOLD);
      launchAdjust = 0;
      bool isAngleHigh = true;
      bool isAngleLow = false;
    }

}

void setStateLaunchAdjustHi()
{
  startAngleAdjustHi.notify();
}

pros::Task startAngleAdjustLow (launchAdjustLow, NULL, TASK_PRIORITY_DEFAULT,
                                TASK_STACK_DEPTH_DEFAULT,"ANGLE LOW GO!");
void launchAdjustLow( void * param)
{
  while( startAngleAdjustLow.notify_take(true, TIMEOUT_MAX))
  {
      double angleP = -.30;
      int targetPositionAngle = 2960;
      int error = targetPositionAngle - launchAdjustAngle;
      MainController.clear();
      double timeInit = pros::millis();
      double timechange;
      while(abs( error ) > 50 )
      {
        error = targetPositionAngle - launchAdjustAngle;
        timechange = pros::millis() - timeInit;
        launchAdjust = ( angleP * error );
      }
      launchAdjust = launcherAdjuster.set_brake_mode(MOTOR_BRAKE_HOLD);
      launchAdjust = 0;
      bool isAngleHigh = false;
      bool isAngleLow = true;
    }

}

void setStateLaunchAdjustLow()
{
  startAngleAdjustLow.notify();
}


// pros::Task startToggleBallHookOut (hookOut, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "HOOK IT");
//
// void toggleBallHook()
// {
//   bool isHookOut = true;
//   startToggleBallHookOut.notify();
// }

// void hookOut(void* param)
// {
//   while(startToggleBallHookOut.notify_take(true, TIMEOUT_MAX))
//   {
//     double scrapeP = 0.01;
//     int targetPos = - 80;
//     int error = targetPos - scrapeValue;
//     while(abs(error) > 50)
//     {
//       error = targetPos - scrapeValue;
//       scrapeValue = (scrapeP * error);
//     }
//     scrapeValue = 0;
//   }
// }


//////////////////////////////////////////////////////////////////////////////
////////////////////////////// MOTION PROFILES     //////////////////////////
