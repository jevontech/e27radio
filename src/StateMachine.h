/* 
 * File:   StateMachine.h
 * Author: Jeroen Vennegoor op Nijhuis
 *
 * Created on December 12, 2015, 2:34 PM
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

#include "Poco/Logger.h"
#include "Poco/NumberFormatter.h"
#include <string>
#include <vector>

using namespace std;
using Poco::NumberFormatter;

#include "StateMachine_sm.h"

#include "Audioplayer.h"
#include "BluetoothConfig.h"
#include "PulseAudioConfig.h"
#include "LcdController.h"
#include "ButtonListener.h"

//define struct to store radio station URL's 
struct RadioStation {
    std::string name;
    std::string url;
} ;

class StateMachine {
public:
    StateMachine();
    virtual ~StateMachine();

    void Button1Pressed();
    void Button2Pressed();
    void Button3Pressed();
    
    void StartPlaying();
    void StopPlaying();
    void ChannelUp();
    void ChannelDown();


private:
    Poco::Logger& logger;
    StateMachineContext _fsm;
    Poco::Thread audiothread;
    std::vector<RadioStation> radiostations;
    int selectedRadiostation;
    ButtonListener* buttonlistener;
    LcdController* lcd;
    BluetoothConfig* bluetoothconfig;
    PulseAudioConfig* pulseaudioconfig;
    Audioplayer* player;

};

#endif	/* STATEMACHINE_H */

