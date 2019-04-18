#include "main.h"


//void hookOut(void* param);
void launchAdjustHi(void* param);
void launchAdjustLow(void* param);

extern void toggleBallHook();

extern void setStateLaunchAdjustHi();
extern void setStateLaunchAdjustLow();



extern void intakeIn();
extern void intakeOut();
extern void intakeStop();

extern bool isAngleHigh;
extern bool isAngleLow;
