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

#ifndef __NIXIE_DYNAMIC_H__
#define __NIXIE_DYNAMIC_H__

#include <stdint.h>
#include <Arduino.h>

class Nixie
{
private:
    uint8_t decoder[4]; /* BCD decoder pins (A1, B2, C4, D8) */
    uint8_t * digits; /* Anode key pins */
    uint8_t digitsNum; /* Number of digits 1-8 */
    uint8_t actLevel; /* Active level for anode keys (HIGH or LOW) */
    uint32_t number; /* Number to display */
    uint8_t cDigit; /* Current digit */
    uint32_t cDiv; /* Current divider */
    uint32_t cTime; /* Current time for dynamic indication, us */

    void showNumber(void);

public:
    Nixie(uint8_t, uint8_t, uint8_t, uint8_t);
    void begin(void);
    void setDigits(uint8_t *, uint8_t, uint8_t);
    void setNumber(uint32_t);
    uint32_t getNumber(void);
    void clear(void);
    void loop(uint32_t);
};

#endif /* ~__NIXIE_DYNAMIC_H__ */
