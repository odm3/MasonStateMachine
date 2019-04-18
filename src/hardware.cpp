#include "hardware.h"
#include "deviceDefinitions.h"

int armSustain = 0;
int armPosition = 0;
int launchAdjustAngle = 0;
int autoAngleVal;

int armSpeed =0;
double baseLeft = 0.00;
double baseRight = 0.00;

int LowerIntakeSpeed = 0;
int UpperIntakeSpeed = 0;

int launch = 0;
int launchAdjust = 0;

int ballDetectIntakeVal = 0;
int ballDetectLauncherVal = 0;
int launcherPullbackDetectorVal =0;
int scrapeValue = 0;

auto drive = ChassisControllerFactory::create
(
    leftDrive,
    rightDrive,
    AbstractMotor::gearset::green,
    {4_in, 15_in}
);


//        Motionprogile controller with something else?
//static AsyncMotionProfileController baseMPController(1.0, 2.0, 10.0, drive, {4_in, 15_in}, );


void inputs()
{
    scrapeValue = capScraper.getPosition();
    launchAdjustAngle = LaunchAnglePot.get_value();
    ballDetectIntakeVal = ballDetectIntake.get_value();
    ballDetectLauncherVal = ballDetectLauncher.get_value();
    launcherPullbackDetectorVal = launcherPullbackDetector.get_value();
  
}


void outputs()
{
    drive.tank(baseLeft, baseRight);
    LowerIntake.move(LowerIntakeSpeed);
    UpperIntake.move(UpperIntakeSpeed);
    launcher.moveVelocity(launch);
    launcherAdjuster.move(launchAdjust);
}

pros::Task startOutputTask(initHardwareTasks, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT,
                            "Setter Getter GO!");

void initHardwareTasks( void* param)
{
  while(startOutputTask.notify_take(true, TIMEOUT_MAX))
  {
    outputs();
    inputs();
  }
}
