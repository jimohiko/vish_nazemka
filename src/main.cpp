#include <Arduino.h>
#include "config.h"
#include "Sensors/Sensors.h"
#include "rotation_system/rotation_system.h"


void setup() {
    Serial.begin(9600);
    
    pinMode(LED_BUILTIN, OUTPUT);

    rotationSystemInit();
}


int tickIndicator = 0;

void loop() {
    rotationSystemTest();
    if (++tickIndicator >= 50000) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        tickIndicator = 0;
    }
}
