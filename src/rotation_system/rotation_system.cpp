#include "rotation_system.h"
TinyStepper_28BYJ_48 myStepper;
Servo myServo;


void setRotation(int16_t setCorner);


/*иницыализацыя системы поворота*/
void rotationSystemInit() {
    myStepper.connectToPins(STEPPER_PIN_IN1, STEPPER_PIN_IN2, STEPPER_PIN_IN3, STEPPER_PIN_IN4);
    myStepper.setSpeedInStepsPerSecond(STEPPER_SPEED);
    myStepper.setAccelerationInStepsPerSecondPerSecond(STEPPER_ACCELERATION);
    myServo.attach(SERVO_PIN);
    myServo.write(90);
    delay(100);
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
    return((degree * PI_NUMBER) / 180);
}

/*функцыя конвертацыя радиан в градусы*/
double convertingRadianToDegree(double radian) {
    return((radian * 180) / PI_NUMBER);
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

/*вычисление растояния при помоши функции "гаверсинус"*/
double distancesHaversine(double stationWidth, double stationLongitude, double objectWidth, double objectLongitude) {
    /*конвертацыя градусов в радианы*/
    stationLongitude = convertingDegreeToRadian(stationLongitude);
    stationWidth = convertingDegreeToRadian(stationWidth);
    objectLongitude = convertingDegreeToRadian(objectLongitude);
    objectWidth = convertingDegreeToRadian(objectWidth);
    /*вычислуния*/
    double deltaLongitude = objectLongitude - stationLongitude;
    double deltawidth = objectWidth - stationWidth;
    double rezult = asin(sqrt((1 - cos(deltawidth) + cos(stationWidth) * cos(objectWidth) * (1 - cos(deltaLongitude))) / 2));

    return(2 * DIAMETER_OF_EARTH * rezult);
}


/*функцыя наведения системы поворота*/
void guidanceRotationSystem(double magneticAzimuth, double stationWidth, double stationLongitude, double stationHeight , double objectWidth, double objectLongitude, double objectHeight){
    setRotation(360 - magneticAzimuth + azimuth(stationWidth, stationLongitude, objectWidth, objectLongitude));
    myServo.write(convertingRadianToDegree(atan((objectHeight - stationHeight) / distancesHaversine(stationWidth, stationLongitude, objectWidth, objectLongitude))) + 90);
}

