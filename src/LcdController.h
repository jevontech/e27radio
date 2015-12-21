/* 
 * File:   LcdController.h
 * Author: Jeroen Vennegoor op Nijhuis
 *
 * Created on December 11, 2015, 2:48 PM
 */

#ifndef LCDCONTROLLER_H
#define	LCDCONTROLLER_H

#include "jhd1313m1.h"   // Lcd Display
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#define LCD_ADDRESS     (0x7c>>1)
#define RGB_ADDRESS     (0xc4>>1)

using namespace std;

class LcdController {
public:
    LcdController();
    void SetLine1(string input);
    void SetLine2(string input);
    void Clear();

    virtual ~LcdController();
private:
    upm::Jhd1313m1 *lcd;
};

#endif	/* LCDCONTROLLER_H */

