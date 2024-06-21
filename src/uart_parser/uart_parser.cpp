#include "uart_parser.h"
void uartParserInit() {
    parserSerial.begin(PARSER_SERIAL_SPEED);
}

char uartBuf[30];
bool comandUpdeteFlag = false;
#if UART_PARSER_TEST == true
void uartParserTest() {
    if (parserSerial.available() > 0) {
        int amount = parserSerial.readBytesUntil(';', uartBuf, 30);
        uartBuf[amount] = NULL;
        Serial.println(uartBuf);
        comandUpdeteFlag = true;
    }
    
    char* ptrs[10];       // указатели на строки
    int count = 0;        // счётчик подстрок
    char* offset = uartBuf;   // указатель для работы
    while (true) {
        ptrs[count++] = offset;         // запоминаем указатель
        offset = strchr(offset, ',');   // ищем новую запятую
        if (offset) {                   // если это не NULL
            *offset = NULL;               // заменяем запятую на нулл
            offset++;                     // продолжаем
        } else break;                     // иначе покидаем цикл
    }

    if(comandUpdeteFlag == true){
        for (int i = 0; i < count; i++) Serial.println(ptrs[i]);
        comandUpdeteFlag = false;
    }
}
#endif
