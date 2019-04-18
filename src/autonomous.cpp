#include "main.h"
#include "hardware.h"
#include "deviceDefinitions.h"
#include "functions.h"

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


 //        Motion profile controller with AsyncControllerFactory
 // auto Autodrive = ChassisControllerFactory::create
 // (
 //     leftDrive,
 //     rightDrive,
 //     AbstractMotor::gearset::green,
 //     {4_in, 15_in}
 // );
 //
 // // //        Motion profile controller with AsyncControllerFactory
 //  auto baseMPController = AsyncControllerFactory::motionProfile(1.0, 2.0, 10.0, Autodrive);
void autonomous()
{
  // startOutputTask.notify();
   // Autodrive.moveDistance(12_in);

    //capScraper.tarePosition();
    //capScraper.setBrakeMode(AbstractMotor::brakeMode::hold);
    generateSkillsPaths();
    //skills();
   blueAuton();
  // baseMPController.generatePath(
  //   {
  //     Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
  //     Point{3_ft, 0_ft, 0_deg}
  //   },  "A"
  // );


}
