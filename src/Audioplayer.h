/*
 * Audioplayer.h
 *
 *  Created on: 25 nov. 2015
 *      Author: Jeroen Vennegoor op Nijhuis
 * 
 * 
 */

#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_


#include "Poco/Logger.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Semaphore.h"
#include "Poco/Mutex.h"
#include <iostream>

#include <curl/curl.h>
#include <mpg123.h>
#include <ao/ao.h>

#define BITS 8

class Audioplayer: public Poco::Runnable {
public:
    Audioplayer();
     virtual ~Audioplayer();
    
    void play(std::string);
    void stop();

    virtual void run();
    size_t play_stream(void *buffer, size_t size, size_t nmemb, void *userp);
    static size_t play_streamWrapper(void *buffer, size_t size, size_t nmemb, void *userp);

private:
    Poco::Logger& logger;
    std::string audioStream;
    bool quitApplication;
    bool playEnabled;
    Poco::Semaphore playSemaphore;
    Poco::Semaphore stopSemaphore;
    int state;

    mpg123_handle *mh;
    ao_device *dev;
    CURL *curl;


};



#endif /* AUDIOPLAYER_H_ */
