// License: BSD 3 Clause
// Copyright (C) 2010, Google Inc. All rights reserved.
// Copyright (C) 2015+, The LabSound Authors. All rights reserved.

#ifndef AudioDestinationMl_h
#define AudioDestinationMl_h

#include "LabSound/core/AudioNode.h"
#include "LabSound/core/AudioBus.h"

#include "internal/AudioDestination.h"

extern "C" {
#include <libswresample/swresample.h>
}
#include <iostream>
#include <deque>
#include <mutex>
#include <cstdlib>
#include <ml_audio.h>
// #include <ml_logging.h>

namespace lab {

class AudioDestinationGeneric : public AudioDestination
{ 

public:

    AudioDestinationGeneric(AudioIOCallback &, float sampleRate);
    virtual ~AudioDestinationGeneric();

    virtual void start() override;
    virtual void stop() override;
    virtual void startRecording() override;
    virtual void stopRecording() override;

    bool isPlaying() override { return m_isPlaying; }
    bool isRecording() override { return m_isRecording; }
    float sampleRate() const override { return m_sampleRate; }

// protected:

    // void configure();

    AudioIOCallback &m_callback;

    AudioBus m_renderBus = {2, AudioNode::ProcessingSizeInFrames, false};
    AudioBus m_inputBus = {1, AudioNode::ProcessingSizeInFrames, false};

    struct SwrContext *output_swr_ctx;
    struct SwrContext *input_swr_ctx;
    
    float m_sampleRate;
    bool m_isPlaying = false;
    bool m_isRecording = false;
    
    AudioDestinationGenericImpl *audioDestinationGenericImpl;
};

// int outputCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData ); 

} // namespace lab

#endif // AAudioDestinationMl_h

