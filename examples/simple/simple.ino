#include <NixieDynamic.h>

Nixie timer(2, 4, 5, 3);
uint8_t digits[3] = {8, 7, 6};

void setup()
{
    /* Setup anode keys */
    timer.setDigits(digits, sizeof(digits), LOW);
    timer.setNumber(0); /* Initial value */
    timer.begin(); /* Configure pins */
}

void loop()
{
    static uint32_t tSec;
    uint32_t t = millis();

    /* Indication */
    timer.loop(100);

    if (t - tSec >= 1000) {
        /* Every second */
        timer.setNumber(timer.getNumber() + 1);
        tSec = t;
    }
}
