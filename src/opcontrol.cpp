#include "main.h"
#include "hardware.h"
#include "stateMachine.h"
#include "deviceDefinitions.h"
#include "functions.h"
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	capScraper.setBrakeMode(AbstractMotor::brakeMode::hold);
	int BallInIntake = 1300;   	//Value for Ball being in lower Intake
	int BallInLauncher = 1810;	//Value when ball is seen in launcher
	int maxHighAngle = 3570;		// Maximum angle that the launcher can aim upward
	int maxLowAngle = 2249;			//Maximum angle that the launcher can aim downward
	int linearPuncherSeen = 0;	// Value when LP is not seen
	bool GoUp = false;					// Boolean that controls whether Angle adjust goes up or down
	bool intakeGoIn = true;			// Boolean that controls the toggl states for the itnake (in or stop)
	bool usingToggle = false;		// Boolean that lets me know if we are currently using toggle logic or interrupt

	while (true)
	{
		startOutputTask.notify(); 	//Task that does Global Setter/Getter
		sensorDisplayTask.notify();

///////////////////////////////		BASE Control			////////////////////////////
		baseLeft = MainController.getAnalog(ControllerAnalog::leftY);		//Sets left side of base to joystick val
		baseRight = MainController.getAnalog(ControllerAnalog::rightY);	// Sets right side of base to Joystick Val
///////////////////////////////		LAUNCHER Control		///////////////////////////
		/**	@Brief:
						-- If the button is pushed and theres a ball in the launcher launch
						-- If button is not pushed and there sensor doesnt see the puncher, pull Back
						-- Once the sensor sees the puncher stop

			 @FLAWS:
			 			-- Cannot fire without there being a ball in the launcher
		*/
		if(toggleLaunch.isPressed() && ballDetectLauncherVal < BallInLauncher) // if the button is pushed and no ball is seen
		{
			launch = 127;
		}
		else
		{
			if(launcherPullbackDetectorVal == linearPuncherSeen)
			{
				launch = 127;
			}
			else
			{
				launch =0;
			}
		}

///////////////////////////////		INTAKE  Control		///////////////////////////
		if(toggleIntakeHold.isChangedToPressed())
		{
			if(intakeGoIn == true)
			{
				LowerIntakeSpeed = 127;
				UpperIntakeSpeed = 127;
				intakeGoIn = false;
			}
			else
			{
				LowerIntakeSpeed = 0;
				UpperIntakeSpeed = 0;
				intakeGoIn = true;
			}
			usingToggle = true;
		}
		if(usingToggle)
		{
			if(ballDetectIntakeVal> BallInIntake && ballDetectLauncherVal < BallInLauncher)
			{
				LowerIntakeSpeed = 0;
				UpperIntakeSpeed = 0;
				MainController.rumble("...");
			}
		}
		if(toggleIntakeIn.isPressed() && toggleIntakeOut.isPressed())
		{
			usingToggle = false;
			intakeGoIn = true;

			if(ballDetectIntakeVal> BallInIntake && ballDetectLauncherVal < BallInLauncher)
			{
				LowerIntakeSpeed = 0;
				UpperIntakeSpeed = 0;
				MainController.rumble("...");
			}
			else
			{
				LowerIntakeSpeed = 127;
				UpperIntakeSpeed = 127*.7;
			}
		}
		else if (toggleIntakeIn.isPressed())
		{
			usingToggle = false;
			intakeGoIn = true;

			if(ballDetectIntakeVal> BallInIntake && ballDetectLauncherVal < BallInLauncher)
			{
				LowerIntakeSpeed = 0;
				UpperIntakeSpeed = 0;
				MainController.rumble("...");
			}
			else
			{
				LowerIntakeSpeed = 127;
				UpperIntakeSpeed = 127*.7;
			}

		}
		else if (toggleIntakeOut.isPressed())
		{
			usingToggle = false;
			intakeGoIn = true;

			LowerIntakeSpeed = -127;
			UpperIntakeSpeed = -127*.8;

		}
		else
		{
			if(usingToggle = false)
			{
				LowerIntakeSpeed = 0;
				UpperIntakeSpeed = 0;
			}
		}

		///////////////////////////////		ANGLE  Control		///////////////////////////

		if (toggleAngle.changedToPressed())
		{
			if(GoUp == true)
			{
				setStateLaunchAdjustHi();
				GoUp = false;
			}
			else
			{
				setStateLaunchAdjustLow();
				GoUp = true;
			}
		}

		if(toggleLaunchAdjustLo.isPressed())
		{
			if(launchAdjustAngle < maxHighAngle)
			{
				launchAdjust = -127;
			}
			else
			{
				launchAdjust = 0;
			}
		}
		else if(toggleLaunchAdjustHi.isPressed())
		{
			if(launchAdjustAngle > maxLowAngle)
			{
				launchAdjust = 127;
			}
			else
			{
				launchAdjust = 0;
			}
		}
		else
		{
			launchAdjust = 0;
		}

///////////////////////////////		SCRAPPER  Control		///////////////////////////
		if(toggleScrapeDown.isPressed())
		{
			capScraper.moveAbsolute(90,100);
		}
		else
		{
			capScraper.moveAbsolute(-5,50);
		}

		pros::delay(20);
	}
}
