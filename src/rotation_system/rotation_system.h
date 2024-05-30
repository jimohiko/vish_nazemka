#ifndef STEPPER_H
#define STEPPER_H
#include <Arduino.h>
#include <cmath>
#include "TinyStepper_28BYJ_48.h"
#include "config.h"

void rotationSystemInit();      //функцыя иницыализации системы поворота. вызывать в setup
void guidanceRotationSystem(double magneticAzimuth, double stationWidth, double stationLongitude, double objectWidth, double objectLongitude, double objectHeight);
void rotationSystemTest();

#endif
