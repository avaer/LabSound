#ifndef AudioDestinationGenericImpl_h
#define AudioDestinationGenericImpl_h

#include <functional>

class AudioDestinationGenericImpl;
AudioDestinationGenericImpl *adgCreate(float sampleRate, std::function<void(int numberOfFrames, void *outputBuffer, void *inputBuffer)> renderFn);
void adgDestroy(AudioDestinationGenericImpl *audioDestinationGenericImpl);
bool adgStart(AudioDestinationGenericImpl *audioDestinationGenericImpl);
bool adgStop(AudioDestinationGenericImpl *audioDestinationGenericImpl);
bool adgStartRecording(AudioDestinationGenericImpl *audioDestinationGenericImpl);
bool adgStopRecording(AudioDestinationGenericImpl *audioDestinationGenericImpl);

#endif
