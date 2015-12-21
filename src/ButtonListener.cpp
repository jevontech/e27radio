/* 
 * File:   ButtonListener.cpp
 * Author: Jeroen Vennegoor op Nijhuis
 * 
 * Created on December 12, 2015, 12:32 PM
 */

#include "Poco/LogStream.h"

#include "ButtonListener.h"
#include "StateMachine.h"

//we need a global variable in order to use a non-static C++ member function 
//as function pointer (callback) in  mraa_gpio_isr()
void* pt2Object;

ButtonListener::ButtonListener(StateMachine* statemachine) :
logger(Poco::Logger::get("ButtonListener")),
previousButtonPress(), currentButtonPress(),
m_button1(), m_button2(), m_button3() {

    this->statemachine = statemachine;
    pt2Object = (void*) this;

    /* initialize MRAA */
    mraa_init();

    //configure button1 (Play&Stop))
    m_button1 = mraa_gpio_init(4);
    mraa_gpio_dir(m_button1, MRAA_GPIO_IN);
    const char* string1 = "button1";
    mraa_gpio_isr(m_button1, MRAA_GPIO_EDGE_RISING, &ButtonPressedWrapper, (void*) string1);

    //configure button2 (Up)
    m_button2 = mraa_gpio_init(3);
    mraa_gpio_dir(m_button2, MRAA_GPIO_IN);
    const char* string2 = "button2";
    mraa_gpio_isr(m_button2, MRAA_GPIO_EDGE_RISING, &ButtonPressedWrapper, (void*) string2);
    
    //configure button3 (Down)
    m_button3 = mraa_gpio_init(2);
    mraa_gpio_dir(m_button3, MRAA_GPIO_IN);
    const char* string3 = "button3";
    mraa_gpio_isr(m_button3, MRAA_GPIO_EDGE_RISING, &ButtonPressedWrapper, (void*) string3);

}

void ButtonListener::ButtonPressed(char* button) {

    //software debouncing
    //check amount of time between last button pressed and current
    time(&currentButtonPress);

    double timeDifference = difftime(currentButtonPress, previousButtonPress)*1000;

    if (timeDifference > 10) {

        if (strcmp(button, "button1") == 0) {
            statemachine->Button1Pressed();
        }
        if (strcmp(button, "button2") == 0) {
            statemachine->Button2Pressed();
        }
        if (strcmp(button, "button3") == 0) {
            statemachine->Button3Pressed();
        }

        time(&previousButtonPress);

    }
}

void ButtonListener::ButtonPressedWrapper(void* input) {
    ButtonListener* mySelf = (ButtonListener*) pt2Object;
    char* string = (char*) input;
    mySelf->ButtonPressed(string);
}

ButtonListener::~ButtonListener() {
    mraa_gpio_close(m_button1);
    mraa_gpio_close(m_button2);
    mraa_gpio_close(m_button3);

}

