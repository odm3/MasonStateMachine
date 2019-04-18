#include "deviceDefinitions.h"
#include "hardware.h"
#include "stateMachine.h"
#include "functions.h"


auto autoDrive = ChassisControllerFactory::create
(
    leftDrive,
    rightDrive,
    AbstractMotor::gearset::green,
    {3.92_in, 11_in}
);
auto baseMPController = AsyncControllerFactory::motionProfile(1.0, 2.0, 10.0, autoDrive);
std::string text("autoTask");
std::string text2("sensorTask");
pros::Task autonDisplayTask (autonSelect, &text);
pros::Task sensorDisplayTask(sensorDisplay, &text2);


void shoot()
{
  launcher.moveVelocity(100);
  pros::delay(1000);
  launcher.moveVelocity(0);
}



void blueAuton()
{
  ////////////////////  Pre movement calibrations //////////////////////////
  capScraper.tarePosition();
  ////////////////////  Shoot preload and ram bottom flag ////////////////////
  pros::delay(1000);
  setStateLaunchAdjustHi();
  shoot();
  LowerIntake.moveVelocity(100);
  UpperIntake.moveVelocity(300);
  baseMPController.setTarget("RamBottomLeft");
  baseMPController.waitUntilSettled();
  ////////////////////  Back up, turn to red cap with balls/////////////////////
  LowerIntake.moveVelocity(0);
  UpperIntake.moveVelocity(0);
  autoDrive.setMaxVelocity(75);
  autoDrive.moveDistance(-2.67_ft);
  autoDrive.setMaxVelocity(20);
  autoDrive.turnAngle(-87.5_deg);
  autoDrive.waitUntilSettled();
  ////////////////////  Go towards red Cap and try to scrape balls off//////////
  autoDrive.setMaxVelocity(30);
  LowerIntake.moveVelocity(80);
  UpperIntake.moveVelocity(300);
  autoDrive.moveDistance(10_in);
  autoDrive.waitUntilSettled();
  capScraper.moveRelative(95, 100);
  pros::delay(350);
  autoDrive.setMaxVelocity(50);
  autoDrive.moveDistance(-5_in);
  autoDrive.moveDistance(2_in);
  autoDrive.moveDistance(-2_in);
  autoDrive.moveDistance(2_in);
  autoDrive.moveDistance(-10_in);
  ////////////////////////    UNTESTED AUTON BELOW    ////////////////
  capScraper.moveAbsolute(5,70);
  pros::delay(350);
  LowerIntake.moveVelocity(-300);
  autoDrive.setMaxVelocity(75);
  autoDrive.moveDistance(20_in);
  LowerIntake.moveVelocity(0);
  autoDrive.setMaxVelocity(20);
  autoDrive.turnAngle(-45_deg);
  autoDrive.waitUntilSettled();
  setStateLaunchAdjustLow();
  pros::delay(700);
  shoot();
  setStateLaunchAdjustHi();
  pros::delay(700);
  shoot();
  autoDrive.setMaxVelocity(75);
  autoDrive.moveDistance(65_in);
  pros::delay(7000);
  autoDrive.moveDistance(-70_in);
  LowerIntake.moveVelocity(200);
  UpperIntake.moveVelocity(200);
  autoDrive.setMaxVelocity(20);
  autoDrive.turnAngle(-315_deg);
  autoDrive.waitUntilSettled();
  autoDrive.setMaxVelocity(50);
  autoDrive.moveDistance(35_in);
  autoDrive.waitUntilSettled();
  autoDrive.moveDistance(-5_in);
  autoDrive.waitUntilSettled();
  UpperIntake.moveVelocity(0);
  autoDrive.setMaxVelocity(20);
  autoDrive.turnAngle(-270_deg);
  autoDrive.waitUntilSettled();
  autoDrive.moveDistance(40_in);
  autoDrive.setMaxVelocity(20);
  autoDrive.turnAngle(-315_deg);
  LowerIntake.moveVelocity(100);
  autoDrive.moveDistance(10_in);
  capScraper.moveRelative(90,100);
  pros::delay(350);
  autoDrive.moveDistance(-5_in);
  autoDrive.moveDistance(5_in);
  LowerIntake.moveVelocity(10);
  //Wait some amount of time
  //aim at mid flag
  // shoot
  //park

}
void redAuton()
{

}
void skills()
{
  // capScraper.moveRelative(-82, 200);
  // autoDrive.setMaxVelocity(50);
  // LowerIntake.moveVelocity(200);
  // pros::delay(2000);
  // autoDrive.moveDistance(-0.25_ft);
  // //LowerIntake.moveVelocity(0);
  // capScraper.moveRelative(82, 200);
    capScraper.tarePosition();
    pros::delay(1000);
    setStateLaunchAdjustHi();
    shoot();
    LowerIntake.moveVelocity(100);
    UpperIntake.moveVelocity(300);
    baseMPController.setTarget("RamBottomLeft");
    baseMPController.waitUntilSettled();
    LowerIntake.moveVelocity(0);
    UpperIntake.moveVelocity(0);
    autoDrive.setMaxVelocity(75);
    autoDrive.moveDistance(-2.67_ft);
    autoDrive.setMaxVelocity(20);
    autoDrive.turnAngle(-87.5_deg);
    autoDrive.waitUntilSettled();
    autoDrive.setMaxVelocity(30);
    LowerIntake.moveVelocity(80);
    UpperIntake.moveVelocity(300);
    autoDrive.moveDistance(10_in);
    autoDrive.waitUntilSettled();
    capScraper.moveRelative(95, 100);
    pros::delay(350);
    autoDrive.setMaxVelocity(50);
    autoDrive.moveDistance(-5_in);
    autoDrive.moveDistance(2_in);
    autoDrive.moveDistance(-2_in);
    autoDrive.moveDistance(2_in);
    autoDrive.moveDistance(-10_in);




  //baseMPController.setTarget("FlipCap");
  // autoDrive.moveDistanceAsync(2.25_ft);
  // LowerIntake.moveVelocity(-200);

  // baseMPController.waitUntilSettled();


}

 void generateSkillsPaths()
 {
   baseMPController.generatePath(
    {
      Point{0_ft, 0_ft, 0_deg},
      Point{2.5_ft, -0.125_ft, 0_deg},
      Point{3.75_ft, 0_ft, 0_deg}
    }, "RamBottomLeft"
  );
  baseMPController.generatePath(
    {
      Point{0_ft, 0_ft, 0_deg},
      Point{2_ft, 2_ft, -90_deg}
    }, "FlipCap"
  );
 }

void autonSelect(void* param)
{
  lv_obj_t * autoSelector = lv_label_create(lv_scr_act(), NULL);
  char potBuffer[32];
  std::uint32_t now = pros::millis();
    while(autonDisplayTask.notify_take(true, TIMEOUT_MAX)) {
      switch(autoChoose()) {
        case 0:
          lv_label_set_text(autoSelector, "Red Front");
          break;
        case 1:
          lv_label_set_text(autoSelector, "Red Back");
          break;
        case 2:
          lv_label_set_text(autoSelector, "Blue Front");
          break;
        case 3:
          lv_label_set_text(autoSelector, "Blue Back");
          break;
        case 4:
          lv_label_set_text(autoSelector, "Skills");
          break;
        default:
          lv_label_set_text(autoSelector, "No auto selected");
      }
      pros::Task::delay_until(&now, 100);
  }
}

void sensorDisplay(void* param)
{
  lv_obj_t * ballDetectIntakeValLabel = lv_label_create(lv_scr_act(), NULL);
  lv_obj_t * ballDetectLauncherValLabel = lv_label_create(lv_scr_act(), NULL);
  lv_obj_t * ballDetectIntakeLabel = lv_label_create(lv_scr_act(), NULL);
  lv_obj_t * ballDetectLauncherLabel = lv_label_create(lv_scr_act(), NULL);
  char intakeBuf[64];
  char launcherBuf[64];
  std::uint32_t now = pros::millis();
  lv_obj_set_y(ballDetectIntakeLabel, 20);
  lv_obj_set_x(ballDetectIntakeValLabel, 100);

  lv_obj_set_y(ballDetectLauncherLabel, 40);
  lv_obj_set_x(ballDetectLauncherValLabel, 100);

  lv_obj_set_y(ballDetectIntakeValLabel, 20);
  lv_obj_set_y(ballDetectLauncherValLabel, 40);
  while(sensorDisplayTask.notify_take(true, TIMEOUT_MAX)) {
    sprintf(intakeBuf, "%d", ballDetectIntake.get_value());
    sprintf(launcherBuf, "%d", ballDetectLauncher.get_value());

    lv_label_set_text(ballDetectIntakeLabel, "Intake Val: ");
    lv_label_set_text(ballDetectLauncherLabel, "Launcher Val: ");
    lv_label_set_text(ballDetectIntakeValLabel, intakeBuf);
    lv_label_set_text(ballDetectLauncherValLabel, launcherBuf);
    pros::Task::delay_until(&now, 50);
  }
}

int autoChoose()
{
  return floor(((AutonPot.get() - 14)* 6) / (4095-14));
}
