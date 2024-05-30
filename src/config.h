#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

#define LED_BUILTIN GPIO_NUM_1

/*настройки системы поворота*/
#define STEPPER_SPEED 500               //скорость в Шагах В Секунду
#define STEPPER_ACCELERATION 200       //ускорение в Шагах В Секунду
#define STEPS_PER_REVILUTION 2048       //количество шагов в одном обороте (для шагового 28BYJ-48 2048 шагов)
#define STEPPER_PIN_IN1 GPIO_NUM_13
#define STEPPER_PIN_IN2 GPIO_NUM_12
#define STEPPER_PIN_IN3 GPIO_NUM_14
#define STEPPER_PIN_IN4 GPIO_NUM_27

#endif
