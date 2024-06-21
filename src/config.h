#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

#define LED_BUILTIN GPIO_NUM_21

/*debag*/
#define GPS_TEST false
#define UART_PARSER_TEST true

/*настройки системы поворота*/
#define PI_NUMBER 3.141592653589793     //число пи
#define DIAMETER_OF_EARTH 6371008       //диаметр земли
#define STEPPER_SPEED 950               //скорость шагового двигатиля в Шагах В Секунду
#define STEPPER_ACCELERATION 900        //ускорение шагового двигатиля в Шагах В Секунду
#define STEPS_PER_REVILUTION 2048       //количество шагов в одном обороте (для шагового 28BYJ-48 2048 шагов)
#define STEPPER_PIN_IN1 GPIO_NUM_13
#define STEPPER_PIN_IN2 GPIO_NUM_12
#define STEPPER_PIN_IN3 GPIO_NUM_14
#define STEPPER_PIN_IN4 GPIO_NUM_27
#define SERVO_PIN GPIO_NUM_33           //пин подключения серво привода

/*настройки датчиков*/
#define GPSSerial Serial2               //serial порт к которому подключен gps
#define GPS_SPEED 9600                  //скорость serial для gps

/*настройки парсера*/
#define parserSerial Serial1            //serial порт uart_parser
#define PARSER_SERIAL_SPEED 115200      //скорость serial для uart_parser

#endif
