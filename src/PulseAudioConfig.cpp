/* 
 * File:   PulseAudioConfig.cpp
 * Author: Jeroen Vennegoor op Nijhuis
 * 
 * Created on December 18, 2015, 10:37 AM
 */

#include "PulseAudioConfig.h"

PulseAudioConfig::PulseAudioConfig() : logger(Poco::Logger::get("PulseAudioConfig")) {
}

void PulseAudioConfig::setDefaultSink() {
    std::string pactl("/usr/bin/pactl");
    std::vector<std::string> args;
    args.push_back("list");
    Poco::Pipe outPipe;
    Poco::ProcessHandle ph = Poco::Process::launch(pactl, args, 0, &outPipe, 0);
    Poco::PipeInputStream istr(outPipe);
    std::string output;
    Poco::StreamCopier::copyToString(istr, output);
    Poco::RegularExpression re1("(bluez_sink.[A-Za-z0-9_]*)");
    Poco::RegularExpression::Match pos;

    std::string name;
    int n = re1.extract(output, name);

    logger.information("pactl list: ");
    logger.information(name);

    std::vector<std::string> args2;
    args2.push_back("set-default-sink");
    args2.push_back(name);
    Poco::ProcessHandle ph2 = Poco::Process::launch(pactl,args2);

}

PulseAudioConfig::~PulseAudioConfig() {
}

