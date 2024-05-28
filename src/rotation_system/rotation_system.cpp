#include "rotation_system.h"
TinyStepper_28BYJ_48 myStepper;

void setRotation(int16_t setCorner);

void rotationSystemInit() {
    myStepper.connectToPins(STEPPER_PIN_IN1, STEPPER_PIN_IN2, STEPPER_PIN_IN3, STEPPER_PIN_IN4);
    myStepper.setSpeedInStepsPerSecond(STEPPER_SPEED);
    myStepper.setAccelerationInStepsPerSecondPerSecond(STEPPER_ACCELERATION);
    setRotation(90);
}

int16_t currentRotationAngle = 0;
void setRotation(int16_t setCorner) {
    myStepper.moveRelativeInSteps(map(setCorner, -360, 360, -STEPS_PER_REVILUTION, STEPS_PER_REVILUTION));
}

void rotationSystemTest() {
    setRotation(-90);
    delay(200);
}
