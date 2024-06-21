#include "Sensors/Sensors.h"
#define HMC5883L_ADDRESS (0x1E) // Адрес магнитометра


TinyGPSPlus GPS;
// MPU6050 mpu;

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345); // Айди магнитометра

void sensorsInit() {
  GPSSerial.begin(GPS_SPEED);
}

double getAzimutComps() {
  sensors_event_t event;
  mag.getEvent(&event);

  double heading = atan2(event.magnetic.y, event.magnetic.x); // Получаем угол
  double headingDegrees = heading * 180 / M_PI;
  return headingDegrees;
}

double gpsWidth = 0;
double gpsLongitude = 0;
void getGpsData() {
  if (GPSSerial.available()) {
    GPS.encode(GPSSerial.read());
  }
  if (GPS.location.isUpdated()) {
    gpsWidth = GPS.location.lat();
    gpsLongitude = GPS.location.lng();
  }
}

double getGpsWidth() {
  return(gpsWidth);
}
double getGpsLongitude() {
  return(gpsLongitude);
}

#if GPS_TEST == true
void sensorTest() {
  Serial.print("\n");
  Serial.print(getGpsWidth(), 6);
  Serial.print(", ");
  Serial.print(getGpsLongitude(), 6);
}
#endif

// void getAndPrintSensorData() {
//   int16_t ax, ay, az;
//   int16_t gx, gy, gz;

//   // mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

//   Serial.print("Ускорение: ");
//   Serial.print("X = "); Serial.print(ax);
//   Serial.print(", Y = "); Serial.print(ay);
//   Serial.print(", Z = "); Serial.print(az);

//   Serial.print(" Гироскоп: ");
//   Serial.print("X = "); Serial.print(gx);
//   Serial.print(", Y = "); Serial.print(gy);
//   Serial.print(", Z = "); Serial.println(gz);
// }
