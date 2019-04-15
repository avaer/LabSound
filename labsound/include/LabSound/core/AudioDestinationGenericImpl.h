#ifndef AudioDestinationGenericImpl_h
#define AudioDestinationGenericImpl_h

#include <functional>

namespace lab {

extern void *(*adgCreate)(float sampleRate, std::function<void(int numberOfFrames, void *outputBuffer, void *inputBuffer)> renderFn);
extern void (*adgDestroy)(void *audioDestinationGenericImpl);
extern bool (*adgStart)(void *audioDestinationGenericImpl);
extern bool (*adgStop)(void *audioDestinationGenericImpl);
extern bool (*adgStartRecording)(void *audioDestinationGenericImpl);
extern bool (*adgStopRecording)(void *audioDestinationGenericImpl);

}

#endif
