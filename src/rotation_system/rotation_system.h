#ifndef STEPPER_H
#define STEPPER_H
#include <Arduino.h>
#include <cmath>
#include <ESP32Servo.h>
#include "TinyStepper_28BYJ_48.h"
#include "config.h"

void rotationSystemInit();      //функцыя иницыализации системы поворота. вызывать в setup
void guidanceRotationSystem(double magneticAzimuth, double stationWidth, double stationLongitude, double stationHeight , double objectWidth, double objectLongitude, double objectHeight);

#endif
