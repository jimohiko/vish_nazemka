#include <Arduino.h>
#include "config.h"
#include "Sensors/Sensors.h"
#include "uart_parser/uart_parser.h"
#include "rotation_system/rotation_system.h"


int tickIndicator = 0;

void setup() {
    Serial.begin(115200);
    Serial.print(".");
    pinMode(LED_BUILTIN, OUTPUT);

    uartParserInit();
    sensorsInit();
    // rotationSystemInit();
}

void loop() {
    if (++tickIndicator >= 50000) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        Serial.print(".");
    #if UART_PARSER_TEST == true
    uartParserTest();
    #endif
        tickIndicator = 0;
    }
    
    getGpsData();
    // rotationSystemInit(0, getGpsWidth, getGpsLongitude, 0, 0, 0, 0);
    
    #if GPS_TEST == true
    sensorTest();
    #endif

}
