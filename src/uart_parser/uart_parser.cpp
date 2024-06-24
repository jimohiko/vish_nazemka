#include "uart_parser.h"
void uartParserInit() {
    parserSerial.begin(PARSER_SERIAL_SPEED);
}

char uartBuf[30];
bool comandUpdeteFlag = false;
#if UART_PARSER_TEST == true
void uartParserTest() {
    if (parserSerial.available() > 0 && comandUpdeteFlag == false) {
        uartBuf[0] = 0;
        if (parserSerial.find("GPS:")) {
            int amount = parserSerial.readBytesUntil(';', uartBuf, 30);
            uartBuf[amount] = NULL;
            Serial.print(amount);
            comandUpdeteFlag = true;
        }
        Serial.print(" text: ");
        Serial.println(uartBuf);
    }

    static char* ptrs[10];       // указатели на строки
    static int count = 0;        // счётчик подстрок
    static char* offset = uartBuf;   // указатель для работы
    count = 0;
    offset = uartBuf;
    if (comandUpdeteFlag == true) {
        while (true) {
            ptrs[count++] = offset;         // запоминаем указатель
            offset = strchr(offset, ',');   // ищем новую запятую
            if (offset) {                   // если это не NULL
                *offset = NULL;               // заменяем запятую на нулл
                offset++;                     // продолжаем
            } else break;                     // иначе покидаем цикл
        }

        for (int i = 0; i < count; i++) {
            Serial.print("\t");
            Serial.println(ptrs[i]);
        }
        comandUpdeteFlag = false;
    }
}
#endif
