/* 
 * File:   ButtonListener.h
 * Author: Jeroen Vennegoor op Nijhuis
 *
 * Created on December 12, 2015, 12:32 PM
 */

#ifndef BUTTONLISTENER_H
#define	BUTTONLISTENER_H

#include "Poco/Logger.h"
#include <mraa/gpio.h>
#include <time.h> 

class StateMachine;

class ButtonListener {
public:
    ButtonListener(StateMachine* statemachine);
    void ButtonPressed(char*);
    static void ButtonPressedWrapper(void*);
    virtual ~ButtonListener();
private:
    Poco::Logger& logger;
    StateMachine* statemachine;
    time_t previousButtonPress;
    time_t currentButtonPress;
    mraa_gpio_context m_button1;
    mraa_gpio_context m_button2;
    mraa_gpio_context m_button3;

};

#endif	/* BUTTONLISTENER_H */

