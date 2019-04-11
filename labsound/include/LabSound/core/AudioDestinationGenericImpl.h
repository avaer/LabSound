#ifndef AudioDestinationGenericImpl_h
#define AudioDestinationGenericImpl_h

#include <functional>

void *adgCreate(float sampleRate, std::function<void(int numberOfFrames, void *outputBuffer, void *inputBuffer)> renderFn);
void adgDestroy(void *audioDestinationGenericImpl);
bool adgStart(void *audioDestinationGenericImpl);
bool adgStop(void *audioDestinationGenericImpl);
bool adgStartRecording(void *audioDestinationGenericImpl);
bool adgStopRecording(void *audioDestinationGenericImpl);

#endif
