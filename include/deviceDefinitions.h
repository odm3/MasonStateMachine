#include "main.h"
#pragma once
extern MotorGroup leftDrive;
extern MotorGroup rightDrive;
extern MotorGroup launcher;
extern Motor LowerIntake;
extern Motor UpperIntake;
extern Motor capScraper;
extern Motor launcherAdjuster;
extern ADIGyro turnyBoi;

extern Controller MainController;

extern pros:: ADIAnalogIn ballDetectIntake;
extern pros::ADILineSensor ballDetectLauncher;
extern pros::ADIDigitalIn launcherPullbackDetector;
extern pros:: ADIPotentiometer LaunchAnglePot;
extern Potentiometer AutonPot;

/** These buttons toggle the actions to take */
extern ControllerButton toggleIntakeIn;
extern ControllerButton toggleIntakeOut;
extern ControllerButton toggleLaunch;
extern ControllerButton toggleLaunchAdjustHi;
extern ControllerButton toggleLaunchAdjustLo;
extern ControllerButton toggleAngle;
extern ControllerButton toggleAuto;
extern ControllerButton toggleIntakeHold;
extern ControllerButton toggleScrapeDown;
extern pros::Task autonDisplayTask;
extern pros::Task sensorDisplayTask;
