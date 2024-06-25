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
                *offset = 0;               // заменяем запятую на нулл
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

double getDoubleFromChar(char *p) {
	static double res;
	static double divider;
	res = 0;
	divider = 0;
	while (*p && *p == ' ') {
		++p;
	}
	while (*p) {
		if (*p == '.') {
			divider = 1;
			++p;
			continue;
		}
		if (divider) {
			divider *= 10;
		}
		res = res * 10 + (*p - '0');
		++p;
	}
	if (divider > 1) {
		res /= divider;
	}
	return res;
}

double getUartDouble(uint8_t index) {
    if (ptrs[index] ==NULL) return 0;
    if (ptrs[index][0] == 0) return 0;
    #if UART_PARSER_TEST == true
    Serial.print("In uW: ");
    Serial.println(ptrs[index]);
    #endif
    return(getDoubleFromChar(ptrs[index]));
}

#if UART_PARSER_TEST == true
void uartParserTest() {
    uartParserUpdete();
    // Serial.println("\t");
    Serial.println(getUartDouble(enWidth));
    Serial.println(getUartDouble(enLongitude));
    Serial.println(getUartDouble(enAlt));
}
#endif
