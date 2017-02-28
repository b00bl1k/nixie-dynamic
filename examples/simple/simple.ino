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
    uint32_t t;

    /* Indication */
    if (timer.getNumber() < 30) {
        timer.loop(100);

        t = millis();
        if (t - tSec >= 1000) {
            /* Every second */
            uint32_t counter = timer.getNumber() + 1;
            timer.setNumber(counter);
            tSec = t;

            /* Stop indication after 30 seconds */
            if (counter == 30)
                timer.clear();
        }
    }
}
