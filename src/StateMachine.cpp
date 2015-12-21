/* 
 * File:   StateMachine.cpp
 * Author: Jeroen Vennegoor op Nijhuis
 * 
 * Created on December 12, 2015, 2:34 PM
 */

#include "StateMachine.h"

StateMachine::StateMachine() : logger(Poco::Logger::get("StateMachine")),
_fsm(*this), audiothread(), radiostations(5), selectedRadiostation(1) {

    radiostations.at(0).name = "Top hits       ";
    radiostations.at(0).url = "http://pub1.radiotunes.com:80/radiotunes_tophits";
    radiostations.at(1).name = "Oldies      ";
    radiostations.at(1).url = "http://pub1.radiotunes.com:80/radiotunes_oldies";
    radiostations.at(2).name = "Dance hits     ";
    radiostations.at(2).url = "http://pub1.radiotunes.com:80/radiotunes_dancehits";
    radiostations.at(3).name = "Smooth jazz    ";
    radiostations.at(3).url = "http://pub1.radiotunes.com:80/radiotunes_smoothjazz";
    radiostations.at(4).name = "Hit 70s        ";
    radiostations.at(4).url = "http://pub1.radiotunes.com:80/radiotunes_hit70s";

    buttonlistener = new ButtonListener(this);
    lcd = new LcdController();
    bluetoothconfig = new BluetoothConfig();
    pulseaudioconfig = new PulseAudioConfig();
    player = new Audioplayer();
    bluetoothconfig->configure();
    lcd->Clear();
    lcd->SetLine1("Booting E27...");
    Poco::Thread::sleep(2000);
    lcd->Clear();

    pulseaudioconfig->setDefaultSink();
    audiothread.start(*player);
    lcd->SetLine1("Stopped:       ");


}

void StateMachine::Button1Pressed() {
    _fsm.Button1Pressed();
}

void StateMachine::Button2Pressed() {
    _fsm.Button2Pressed();
}

void StateMachine::Button3Pressed() {
    _fsm.Button3Pressed();
}

void StateMachine::StartPlaying() {
    logger.debug("Start playing");
    player->play(radiostations.at(selectedRadiostation).url);

    lcd->SetLine1("Playing:       ");
    lcd->SetLine2(radiostations.at(selectedRadiostation).name);
}

void StateMachine::StopPlaying() {
    logger.debug("Stop playing");
    lcd->SetLine1("Stopped:       ");
    lcd->SetLine2("");
    player->stop();
}

void StateMachine::ChannelUp() {
    player->stop();

    logger.debug("Channel up");
    selectedRadiostation = selectedRadiostation + 1;
    //wraparound        
    if (selectedRadiostation == (signed int) radiostations.size()) {
        selectedRadiostation = 0;
    }
    player->play(radiostations.at(selectedRadiostation).url);
    lcd->SetLine1("Playing:          ");
    lcd->SetLine2(radiostations.at(selectedRadiostation).name);

}

void StateMachine::ChannelDown() {
    player->stop();
    logger.debug("Channel down");
    selectedRadiostation = selectedRadiostation - 1;
    //wraparound        
    if (selectedRadiostation == -1) {
        selectedRadiostation = radiostations.size() - 1;
    }
    player->play(radiostations.at(selectedRadiostation).url);
    lcd->SetLine1("Playing:        ");
    lcd->SetLine2(radiostations.at(selectedRadiostation).name);
}

StateMachine::~StateMachine() {
    lcd->Clear();
    player->stop();
    bluetoothconfig->disconnect();
    Poco::Thread::sleep(1000);
    audiothread.join();

    delete player;
    delete pulseaudioconfig;
    delete bluetoothconfig;
    delete lcd;
    delete buttonlistener;
}

