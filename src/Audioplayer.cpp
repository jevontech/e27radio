#include <iostream>
#include <unistd.h>
#include <string>
#include "Audioplayer.h"

/*
 * Audioplayer.cpp
 *
 *  Created on: 25 nov. 2015
 *      Author: Jeroen Vennegoor op Nijhuis
 * 
 * Partially based on code from:
 * http://hzqtc.github.io/2012/05/play-mp3-with-libmpg123-and-libao.html 
 * 
 */

//TODO: read stream meta data

void* pt2Audioplayer;

Audioplayer::Audioplayer() : logger(Poco::Logger::get("Audioplayer")),
audioStream(), quitApplication(false), playEnabled(false), playSemaphore(0, 1), stopSemaphore(0, 1),  state(0), mh(NULL), dev(NULL), curl(NULL) {
    ao_initialize();
    mpg123_init();
    pt2Audioplayer = (void*) this;
}

Audioplayer::~Audioplayer() {
    logger.debug("Audioplayer: destructor");
    quitApplication = true;
    stop();
    mpg123_exit();
    ao_close(dev);
    ao_shutdown();
}

void Audioplayer::run() {
    try {
        while (quitApplication == false) {
            logger.debug("Run: wait for playSemaphore");
            playSemaphore.wait();

            if (playEnabled) {
                mh = mpg123_new(NULL, NULL);
                mpg123_open_feed(mh);
                curl = curl_easy_init();
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, play_streamWrapper);
                curl_easy_setopt(curl, CURLOPT_URL, audioStream.c_str());
                curl_easy_perform(curl);
                curl_easy_cleanup(curl);
                mpg123_close(mh);
                mpg123_delete(mh);
                logger.debug("Run: set stopSemephore");
                stopSemaphore.set();
            }

        }
    } catch (Poco::Exception& exc) {
        std::cerr << exc.displayText() << std::endl;
    }

}

void Audioplayer::play(std::string stream) {
    logger.debug("Play");

    try {
        if (state == 0) {
            audioStream = stream;
            playEnabled = true;
            logger.debug("Set PlaySemaphore");
            playSemaphore.set();
            state = 1;
        }

    } catch (Poco::Exception& exc) {
        std::cerr << exc.displayText() << std::endl;
    }

}

void Audioplayer::stop() {
    logger.debug("Stop playing");
    if (state == 1) {
        playEnabled = false;
        logger.debug("Run: wait for stopSemaphore");
        stopSemaphore.wait();
        state = 0;
    }
}

size_t Audioplayer::play_streamWrapper(void *buffer, size_t size, size_t nmemb, void *userp) {
    Audioplayer* mySelf = (Audioplayer*) pt2Audioplayer;
    return mySelf->play_stream(buffer, size, nmemb, userp);
}

size_t Audioplayer::play_stream(void *buffer, size_t size, size_t nmemb, void *userp) {
    int err;
    off_t frame_offset;
    unsigned char *audio;
    size_t done;
    ao_sample_format format;
    int channels, encoding;
    long rate;

    mpg123_feed(mh, (const unsigned char*) buffer, size * nmemb);
    do {
        err = mpg123_decode_frame(mh, &frame_offset, &audio, &done);
        switch (err) {
            case MPG123_NEW_FORMAT:
                mpg123_getformat(mh, &rate, &channels, &encoding);
                format.bits = mpg123_encsize(encoding) * BITS;
                format.rate = rate;
                format.channels = channels;
                format.byte_format = AO_FMT_NATIVE;
                format.matrix = 0;
                dev = ao_open_live(ao_default_driver_id(), &format, NULL);
                break;
            case MPG123_OK:
                ao_play(dev, (char*) audio, done);
                break;
            case MPG123_NEED_MORE:
                break;
            default:
                break;
        }
    } while (done > 0);

    if (playEnabled) {
        return size * nmemb;
    } else {
        return 0;
    }
}
