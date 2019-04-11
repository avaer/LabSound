// License: BSD 3 Clause
// Copyright (C) 2010, Google Inc. All rights reserved.
// Copyright (C) 2015+, The LabSound Authors. All rights reserved.

#include "internal/ml/AudioDestinationGeneric.h"
#include "internal/VectorMath.h"

#include "LabSound/core/AudioNode.h"
#include "LabSound/core/AudioIOCallback.h"
#include "LabSound/extended/Logging.h"
#include "LabSound/core/AudioDestinationGenericImpl.h"

namespace lab
{

const float kLowThreshold = -1.0f;
const float kHighThreshold = 1.0f;

AudioDestination *AudioDestination::MakePlatformAudioDestination(AudioIOCallback &callback, unsigned numberOfOutputChannels, float sampleRate)
{
    return new AudioDestinationGeneric(callback, sampleRate);
}

unsigned long AudioDestination::maxChannelCount()
{
    return 2;
}

AudioDestinationGeneric::AudioDestinationGeneric(AudioIOCallback &callback, float sampleRate) : m_callback(callback)
{
  m_sampleRate = sampleRate;
  m_renderBus.setSampleRate(m_sampleRate);
  m_inputBus.setSampleRate(m_sampleRate);
  // configure();

  audioDestinationGenericImpl = adgCreate(sampleRate, [&](int numberOfFrames, void *outputBuffer, void *inputBuffer) -> void {
    // Inform bus to use an externally allocated buffer from rtaudio
    m_renderBus.setChannelMemory(0, (float *)outputBuffer, numberOfFrames);
    m_renderBus.setChannelMemory(1, (float *)outputBuffer + numberOfFrames, numberOfFrames);

    m_inputBus.setChannelMemory(0, (float *)inputBuffer, numberOfFrames);

    // Source Bus :: Destination Bus
    m_callback.render(&m_inputBus, &m_renderBus, numberOfFrames);

    // Clamp values at 0db (i.e., [-1.0, 1.0])
    for (unsigned i = 0; i < m_renderBus.numberOfChannels(); ++i)
    {
        AudioChannel * channel = m_renderBus.channel(i);
        VectorMath::vclip(channel->data(), 1, &kLowThreshold, &kHighThreshold, channel->mutableData(), 1, numberOfFrames);
    }
  });
}

AudioDestinationGeneric::~AudioDestinationGeneric() {
  adgDestroy(audioDestinationGenericImpl);
}

/* void AudioDestinationGeneric::configure()
{
    if (dac->getDeviceCount() < 1)
    {
        LOG_ERROR("No audio devices available");
    }

    dac->showWarnings(true);

    RtAudio::StreamParameters outputParams;
    outputParams.deviceId = dac->getDefaultOutputDevice();
    outputParams.nChannels = 2;
    outputParams.firstChannel = 0;

	auto deviceInfo = dac->getDeviceInfo(outputParams.deviceId);
	LOG("Using Default Audio Device: %s", deviceInfo.name.c_str());

    RtAudio::StreamParameters inputParams;
    inputParams.deviceId = dac->getDefaultInputDevice();
    inputParams.nChannels = 1;
    inputParams.firstChannel = 0;

    unsigned int bufferFrames = AudioNode::ProcessingSizeInFrames;

    RtAudio::StreamOptions options;
    options.flags |= RTAUDIO_NONINTERLEAVED;

    try
    {
        dac->openStream(&outputParams, &inputParams, RTAUDIO_FLOAT32, (unsigned int) m_sampleRate, &bufferFrames, &outputCallback, this, &options);
    }
    catch (RtAudioError & e)
    {
        e.printMessage();
    }
} */

void AudioDestinationGeneric::start()
{
    bool ok = adgStart(audioDestinationGenericImpl);
    if (ok) {
      m_isPlaying = true;
    }
}

void AudioDestinationGeneric::stop()
{
    bool ok = adgStop(audioDestinationGenericImpl);
    if (ok) {
      m_isPlaying = false;
    }

    if (isRecording()) {
      stopRecording();
    }
}

void AudioDestinationGeneric::startRecording()
{
    bool ok = adgStartRecording(audioDestinationGenericImpl);
    if (ok) {
      // m_isRecording = true; // only consider recording started on the first buffer emit
      m_isRecording = true;
    }
}

void AudioDestinationGeneric::stopRecording()
{
    bool ok = adgStopRecording(audioDestinationGenericImpl);
    if (ok) {
      m_isRecording = false;
    }
}

} // namespace lab
