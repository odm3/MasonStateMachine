#include "main.h"


extern double baseLeft;
extern double baseRight;

extern int LowerIntakeSpeed;
extern int UpperIntakeSpeed;

extern int launch;
extern int launchAdjust;


extern int ballDetectIntakeVal;
extern int ballDetectLauncherVal;
extern int launcherPullbackDetectorVal;


extern int armPosition;
extern int launchPosition;
extern int launchAdjustAngle;
extern int scrapeValue;

extern pros::Task startOutputTask;


void inputs();
void outputs();
void initHardwareTasks( void* param );
