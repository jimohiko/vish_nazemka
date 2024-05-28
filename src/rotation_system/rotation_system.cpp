#include "rotation_system.h"
Stepper myStepper(STEPS_PER_REVILUTION, STEPPER_PIN_IN1, STEPPER_PIN_IN2, STEPPER_PIN_IN3, STEPPER_PIN_IN4);

void setRotation(int16_t setCorner);

void rotationSystemInit() {
    myStepper.setSpeed(STEPPER_SPEED);
    // myStepper.step(2038);
    setRotation(90);
}

int16_t currentRotationAngle = 0;
void setRotation(int16_t setCorner) {
    myStepper.step(map(setCorner, -360, 360, -2048, STEPS_PER_REVILUTION));
}

void rotationSystemTest(){
    // setRotation(-90);
    myStepper.step(-1024);
    delay(200);
}
