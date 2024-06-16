#ifndef SENSORS_H
#define SENSORS_H
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_GPS.h>
#include <TinyGPSPlus.h>
#include "config.h"
// #include <MPU6050.h>

void sensorsInit();     //инициализация всех необходимых датчиков
void sensorTest();

#endif
