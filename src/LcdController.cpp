/* 
 * File:   LcdController.cpp
 * Author: Jeroen Vennegoor op Nijhuis
 * 
 * Created on December 11, 2015, 2:48 PM
 */

#include "LcdController.h"

LcdController::LcdController() {
    lcd = new upm::Jhd1313m1(6, LCD_ADDRESS, RGB_ADDRESS);
}

void LcdController::SetLine1(string input) {
    lcd->setCursor(0, 0);
    lcd->write(input);
    
}

void LcdController::SetLine2(string input) {
    lcd->setCursor(1, 1);
    lcd->write(input);
}

void LcdController::Clear(){
    lcd->clear();
}

LcdController::~LcdController() {
    delete lcd;
}

