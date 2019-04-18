#include "main.h"
#include "deviceDefinitions.h"
using namespace okapi::literals;
MotorGroup leftDrive ( {-19, 20, 14, -15});
MotorGroup rightDrive ( {9, -10, -17, 18});
MotorGroup launcher ({ -7,8});
Motor LowerIntake(13);
Motor UpperIntake(-6);
Motor capScraper(-5);
Motor launcherAdjuster(16);

ADIGyro turnyBoi('G', 1);
pros::ADIAnalogIn ballDetectIntake('A');
pros::ADILineSensor ballDetectLauncher('F');
pros::ADIPotentiometer LaunchAnglePot('C');
pros::ADIDigitalIn launcherPullbackDetector('H');
Potentiometer AutonPot('D');

Controller MainController (ControllerId::master);

ControllerButton toggleIntakeIn(ControllerId::master, ControllerDigital::R2);
ControllerButton toggleIntakeOut(ControllerId::master, ControllerDigital::R1);
ControllerButton toggleLaunch(ControllerId::master, ControllerDigital::L2);
ControllerButton toggleAngle(ControllerId::master, ControllerDigital::L1);
ControllerButton toggleLaunchAdjustHi(ControllerId::master, ControllerDigital::up);
ControllerButton toggleLaunchAdjustLo(ControllerId::master, ControllerDigital::down);
ControllerButton toggleScrapeDown(ControllerId::master, ControllerDigital::A);
ControllerButton toggleIntakeHold(ControllerId::master, ControllerDigital::X);
ControllerButton toggleAuto(ControllerId::master, ControllerDigital::left);
