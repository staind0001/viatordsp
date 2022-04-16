#include "svfilter.h"
template <typename SampleType>
viator_dsp::SVFilter<SampleType>::SVFilter()
: mCurrentSampleRate (44100.0f), mQ (0.1f), mCutoff (1000.0f), mRawGain (0.0f), twoPi (juce::MathConstants<float>::twoPi)
, mGlobalBypass (false)
, mGCoeff (0.0), mRCoeff (0.0), mRCoeff2 (0.0), mK (1.0), mInversion (0.0)
, mType (FilterType::kLowPass), mQType (QType::kParametric)
{
    // This needs to be called at initialization or the filter breaks
    setParameter(ParameterId::kQ, mQ);
}

template <typename SampleType>
void viator_dsp::SVFilter<SampleType>::prepare(const juce::dsp::ProcessSpec& spec)
{
    mCurrentSampleRate = spec.sampleRate;
    
    mZ1.assign(spec.numChannels, 0.0);
    mZ2.assign(spec.numChannels, 0.0);
}

template <typename SampleType>
void viator_dsp::SVFilter<SampleType>::setParameter(ParameterId parameter, SampleType parameterValue)
{
    switch (parameter)
    {
        // Filter Type
        case ParameterId::kType: mType = (FilterType)parameterValue; break;
            
        // Filter Q Type
        case ParameterId::kQType: mQType = (QType)parameterValue; break;
            
        // Filter Cutoff
        case ParameterId::kCutoff: mCutoff = parameterValue; break;
            
        // Bandwidth
        case ParameterId::kQ:
        {
            mQ = parameterValue;
            
            //Calculate Zavalishin's damping parameter (Q)
            switch (mQType)
            {
                case kParametric: mRCoeff = 1.0 - mQ; break;
                    
                case kProportional:
                    
                    if (mType == kBandShelf)
                    {
                        mRCoeff = 1.0 - getPeakQ(mRawGain); break;
                    }
                    
                    else
                    {
                        mRCoeff = 1.0 - getShelfQ(mRawGain); break;
                    }
                    
                    break;
            }
            
            break;
        }
            
        // Filter Gain
        case ParameterId::kGain: setGain(parameterValue); break;
            
        // Filter samplerate
        case ParameterId::kSampleRate:
        {
            mCurrentSampleRate = parameterValue;
            break;
        }
            
        // Filter Bypass
        case ParameterId::kBypass: mGlobalBypass = static_cast<bool>(parameterValue); break;
    }
}

template <typename SampleType>
void viator_dsp::SVFilter<SampleType>::setGain(SampleType value)
{
    mGain = pow(10, value * 0.05) - 1.f;
    mRawGain = value;
}

template <typename SampleType>
SampleType viator_dsp::SVFilter<SampleType>::getShelfQ(SampleType value) const
{
    return viator_utils::utils::dbToGain(std::abs(value)) * 0.25f - 0.24f;
}

template <typename SampleType>
SampleType viator_dsp::SVFilter<SampleType>::getPeakQ(SampleType value) const
{
    return viator_utils::utils::dbToGain(std::abs(value)) * 0.2f;
}

template class viator_dsp::SVFilter<float>;
template class viator_dsp::SVFilter<double>;
