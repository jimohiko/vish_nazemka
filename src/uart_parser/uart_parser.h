#ifndef UART_PARSER_H
#define UART_PARSER_H
#include "config.h"

enum indexVale{
    enWidth = 0,
    enLongitude = 1,
    enAlt = 2
};

void uartParserInit();              //иницыализация UART парсера
void uartParserUpdete();                //считование даных с uart
double getUartDouble(uint8_t index);    //получение значения
#if UART_PARSER_TEST == true
void uartParserTest();
#endif

#endif
