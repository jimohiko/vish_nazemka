#include "Sensors/Sensors.h"
#define HMC5883L_ADDRESS (0x1E) // Адрес магнитометра


TinyGPSPlus GPS;
// MPU6050 mpu;

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345); // Айди магнитометра

void sensorsInit() {
  GPSSerial.begin(9600);
}

int getMagData() {
  sensors_event_t event;
  mag.getEvent(&event);

  float heading = atan2(event.magnetic.y, event.magnetic.x); // Получаем угол
  int headingDegrees = heading * 180 / M_PI;

  int headingInt = round(headingDegrees); // Округляем

  return headingInt;
}

int getGpsData() {
  if (GPSSerial.available()) {
    char dataGps = GPSSerial.read();
    Serial.write(dataGps);
    return dataGps;
  }
}

void sensorTest() {
  if (GPSSerial.available()) {
    GPS.encode(GPSSerial.read());
  }
  if (GPS.location.isUpdated()) {
    Serial.print(GPS.location.lat(), 6);
    Serial.print(", ");
    Serial.println(GPS.location.lng(), 6);
  }
}

void getAndPrintSensorData() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  // mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print("Ускорение: ");
  Serial.print("X = "); Serial.print(ax);
  Serial.print(", Y = "); Serial.print(ay);
  Serial.print(", Z = "); Serial.print(az);

  Serial.print(" Гироскоп: ");
  Serial.print("X = "); Serial.print(gx);
  Serial.print(", Y = "); Serial.print(gy);
  Serial.print(", Z = "); Serial.println(gz);
}
