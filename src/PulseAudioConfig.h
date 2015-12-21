/* 
 * File:   PulseAudioConfig.h
 * Author: Jeroen Vennegoor op Nijhuis
 *
 * Created on December 18, 2015, 10:37 AM
 */

#ifndef PULSEAUDIOCONFIG_H
#define	PULSEAUDIOCONFIG_H

#include "Poco/Logger.h"
#include "Poco/Process.h"
#include "Poco/StreamCopier.h"
#include "Poco/Pipe.h"
#include "Poco/PipeStream.h"
#include "Poco/RegularExpression.h"

class PulseAudioConfig {
public:
    PulseAudioConfig();
    virtual ~PulseAudioConfig();
    void setDefaultSink();
private:
    Poco::Logger& logger;
};

#endif	/* PULSEAUDIOCONFIG_H */

