#ifndef __AUDIOSTREAM_H__
#define __AUDIOSTREAM_H__

#include <stdint.h>

class AudioStream
{
public:
    AudioStream();

    bool Running() const;

    bool Start(uint16_t const port);

    void Shutdown();

private:
    int32_t audioSocket;
    int32_t createSocket(uint16_t const port);
};

#endif