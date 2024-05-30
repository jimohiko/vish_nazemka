#include "rotation_system.h"
#define piNumber 3.141592653589793  //число пи
TinyStepper_28BYJ_48 myStepper;


void setRotation(int16_t setCorner);


/*иницыализацыя системы поворота*/
void rotationSystemInit() {
    myStepper.connectToPins(STEPPER_PIN_IN1, STEPPER_PIN_IN2, STEPPER_PIN_IN3, STEPPER_PIN_IN4);
    myStepper.setSpeedInStepsPerSecond(STEPPER_SPEED);
    myStepper.setAccelerationInStepsPerSecondPerSecond(STEPPER_ACCELERATION);
    setRotation(360);
    delay(100);
    setRotation(0);
}

/*функцыя установки градуса поворота шагового привода*/
static int16_t currentRotationAngle = 0;
void setRotation(int16_t setCorner) {
        myStepper.moveRelativeInSteps(map(currentRotationAngle - setCorner, -360, 360, -STEPS_PER_REVILUTION, STEPS_PER_REVILUTION));
    currentRotationAngle = setCorner;
}


/*функцыя конвертацыя градусов в радианы*/
double convertingDegreeToRadian(double degree) {
    return((degree * piNumber) / 180);
}

/*функцыя конвертацыя радиан в градусы*/
double convertingRadianToDegree(double radian) {
    return((radian * 180) / piNumber);
}

/*функцыя вычисление азимута*/
double azimuth(double stationWidth, double stationLongitude, double objectWidth, double objectLongitude) {
    /*конвертацыя градусов в радианы*/
    stationLongitude = convertingDegreeToRadian(stationLongitude);
    stationWidth = convertingDegreeToRadian(stationWidth);
    objectLongitude = convertingDegreeToRadian(objectLongitude);
    objectWidth = convertingDegreeToRadian(objectWidth);
    /*вычисление*/
    double deltaLongitude = objectLongitude - stationLongitude;
    double x = sin(deltaLongitude) * cos(objectWidth);
    double y = cos(stationWidth) * sin(objectWidth) - sin(stationWidth) * cos(objectWidth) * cos(deltaLongitude);
    /*проверка на отрецательное значение*/
    if (convertingRadianToDegree(atan2(x, y)) < 0) {
        return(convertingRadianToDegree(atan2(x, y)) + 360);
    }

    return(convertingRadianToDegree(atan2(x, y)));
}


/*функцыя наведения системы поворота*/
void guidanceRotationSystem(double magneticAzimuth, double stationWidth, double stationLongitude, double objectWidth, double objectLongitude, double objectHeight){
    setRotation(360 - magneticAzimuth + azimuth(stationWidth, stationLongitude, objectWidth, objectLongitude));
}

/*тестовая функцыя на время разроботки*/
void rotationSystemTest() {
    guidanceRotationSystem(310, 0, 60, 0, 70, 5);
}
