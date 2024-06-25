#include "uart_parser.h"
void uartParserInit() {
    parserSerial.begin(PARSER_SERIAL_SPEED);
}

char uartBuf[30];
bool comandUpdeteFlag = false;
char* ptrs[10];       // указатели на строки
int count = 0;        // счётчик подстрок
void uartParserUpdete() {
    if (parserSerial.available() > 0 && comandUpdeteFlag == false) {
        uartBuf[0] = 0;
        if (parserSerial.find("GPS:")) {
            int amount = parserSerial.readBytesUntil(';', uartBuf, 30);
            uartBuf[amount] = NULL;
            #if UART_PARSER_TEST == true
            Serial.print(amount);
            #endif
            comandUpdeteFlag = true;
        }
        #if UART_PARSER_TEST == true
        Serial.print(" text: ");
        Serial.println(uartBuf);
        #endif
    }

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

        #if UART_PARSER_TEST == true
        for (int i = 0; i < count; i++) {
            Serial.print("\t");
            Serial.println(ptrs[i]);
        }
        #endif
        comandUpdeteFlag = false;
    }
}

double uartWidth() {
    // return;
}

#if UART_PARSER_TEST == true
void uartParserTest() {
    uartParserUpdete();
    // Serial.println("\t");
    // Serial.println(uartWidth());
}
#endif
