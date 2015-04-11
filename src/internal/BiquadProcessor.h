/*
 * Copyright (C) 2010, Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef BiquadProcessor_h
#define BiquadProcessor_h

#include "LabSound/core/AudioParam.h"

#include "internal/Biquad.h"
#include "internal/AudioDSPKernel.h"
#include "internal/AudioDSPKernelProcessor.h"
#include "internal/AudioBus.h"

namespace WebCore {

// BiquadProcessor is an AudioDSPKernelProcessor which uses Biquad objects to implement several common filters.

class BiquadProcessor : public AudioDSPKernelProcessor {
public:
    enum FilterType {
        LowPass = 0,
        HighPass = 1,
        BandPass = 2,
        LowShelf = 3,
        HighShelf = 4,
        Peaking = 5,
        Notch = 6,
        Allpass = 7
    };

    BiquadProcessor(float sampleRate, size_t numberOfChannels, bool autoInitialize);

    virtual ~BiquadProcessor();
    
    virtual AudioDSPKernel* createKernel();
        
    virtual void process(ContextRenderLock&, const AudioBus* source, AudioBus* destination, size_t framesToProcess);

    // Get the magnitude and phase response of the filter at the given
    // set of frequencies (in Hz). The phase response is in radians.
    void getFrequencyResponse(ContextRenderLock&,
                              int nFrequencies,
                              const float* frequencyHz,
                              float* magResponse,
                              float* phaseResponse);

    void checkForDirtyCoefficients(std::shared_ptr<AudioContext>);
    
    bool filterCoefficientsDirty() const { return m_filterCoefficientsDirty; }
    bool hasSampleAccurateValues() const { return m_hasSampleAccurateValues; }

    std::shared_ptr<AudioParam> parameter1() { return m_parameter1; }
    std::shared_ptr<AudioParam> parameter2() { return m_parameter2; }
    std::shared_ptr<AudioParam> parameter3() { return m_parameter3; }
    std::shared_ptr<AudioParam> parameter4() { return m_parameter4; }

    FilterType type() const { return m_type; }
    void setType(FilterType);

private:
    FilterType m_type;

    std::shared_ptr<AudioParam> m_parameter1;
    std::shared_ptr<AudioParam> m_parameter2;
    std::shared_ptr<AudioParam> m_parameter3;
    std::shared_ptr<AudioParam> m_parameter4;

    // so DSP kernels know when to re-compute coefficients
    bool m_filterCoefficientsDirty;

    // Set to true if any of the filter parameters are sample-accurate.
    bool m_hasSampleAccurateValues;
};

} // namespace WebCore

#endif // BiquadProcessor_h