#include <Arduino.h>
#include "config.h"
#include "Sensors/Sensors.h"
#include "uart_parser/uart_parser.h"
#include "rotation_system/rotation_system.h"

double objectWidth = 0;
double objectLongitude = 0;
double objectAlt = 0;

int tickIndicator = 0;

void setup() {
    Serial.begin(115200);
    Serial.print(".");
    pinMode(LED_BUILTIN, OUTPUT);

    uartParserInit();
    sensorsInit();
    rotationSystemInit();
}

void loop() {
    if (++tickIndicator >= 50000) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        Serial.print(".");
        tickIndicator = 0;
    }

#if UART_PARSER_TEST == true
    uartParserTest();
#endif

    if (uartParserUpdete()) {
        Serial.print("\n\tuart: ");
        Serial.print(getUartDouble(enWidth), 6);
        Serial.print(" ");
        Serial.print(getUartDouble(enLongitude), 6);
        Serial.print("\tGPS: ");
        Serial.print(getGpsWidth(), 6);
        Serial.print(" ");
        Serial.print(getGpsLongitude(), 6);
        objectWidth = getUartDouble(enWidth);
        objectLongitude = getUartDouble(enLongitude);
        objectAlt = getUartDouble(enAlt);
    }


    getGpsData();
    guidanceRotationSystem(0, getGpsWidth(), getGpsLongitude(), 109, objectWidth, objectLongitude, objectAlt);
    rotationRun();

#if GPS_TEST == true
    sensorTest();
#endif

}
