#include "utils.h"

void write_int(long num) {
    if (num == 0) {
        write(1, "0", 1);
        return;
    }
    char buffer[20];
    int i = 0;
    while (num > 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }
    while (i > 0) {
        write(1, &buffer[--i], 1);
    }
}
