/*!
 * Copyright (C) 2017 Alexey Ryabov. All rights reserved.
 *
 * This file may be used under the terms of the GNU Lesser
 * General Public License version 2.1 as published by the Free Software
 * Foundation and appearing in the file LICENSE included in the
 * packaging of this file. Please review the following information to
 * ensure the GNU Lesser General Public License version 2.1 requirements
 * will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 *
 * Author: Alexey Ryabov <6006l1k@gmail.com>
 */

#include <NixieDynamic.h>

#define MAX_DIGITS 8
#define KEY_ON (actLevel)
#define KEY_OFF (!actLevel)

Nixie::Nixie(uint8_t aPin, uint8_t bPin, uint8_t cPin, uint8_t dPin)
{
    decoder[0] = aPin;
    decoder[1] = bPin;
    decoder[2] = cPin;
    decoder[3] = dPin;
}

void Nixie::begin()
{
    for (int pin = 0; pin < sizeof(decoder); pin++) {
        pinMode(decoder[pin], OUTPUT);
        digitalWrite(decoder[pin], HIGH);
    }

    for (int pin = 0; pin < digitsNum; pin++) {
        pinMode(digits[pin], OUTPUT);
        digitalWrite(digits[pin], KEY_OFF);
    }

    cTime = micros();
    cDigit = 0;
    cDiv = 1;
    showNumber();
}

void Nixie::showNumber()
{
    uint8_t num = (number / cDiv) % 10;

    for (int key = 0; key < digitsNum; key++)
        digitalWrite(digits[key], (key == cDigit) ? KEY_ON : KEY_OFF);

    for (int bit = 0; bit < sizeof(decoder); bit++)
        digitalWrite(decoder[bit], (num & (1 << bit)) ? HIGH : LOW);
}

void Nixie::setDigits(uint8_t * pins, uint8_t count, uint8_t activeLevel)
{
    if ((pins == NULL) || (count < 1) || (count > MAX_DIGITS) ||
            (activeLevel > HIGH))
        return;

    digits = pins;
    digitsNum = count;
    actLevel = activeLevel;
}

void Nixie::setNumber(uint32_t value)
{
    number = value;
}

uint32_t Nixie::getNumber()
{
    return number;
}

void Nixie::loop(uint32_t interval)
{
    uint32_t t = micros();
    if (t - cTime < interval)
        return;

    cTime = t;
    cDiv *= 10;
    cDigit++;

    if (cDigit >= digitsNum) {
        cDiv = 1;
        cDigit = 0;
    }

    showNumber();
}
