#ifndef UART_PARSER_H
#define UART_PARSER_H
#include "config.h"

void uartParserInit();              //иницыализация UART парсера
#if UART_PARSER_TEST == true
void uartParserTest();
#endif

#endif
