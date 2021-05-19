//==============================================================================
#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================

JGEQGraphicEqualizerAudioProcessor::JGEQGraphicEqualizerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr),
        PeakFilter1(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 20000.0f, 0.1f, 0.1f)),
        PeakFilter2(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 20000.0f, 0.1f, 0.1f)),
        PeakFilter3(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 20000.0f, 0.1f, 0.1f)),
        PeakFilter4(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 20000.0f, 0.1f, 0.1f)),
        PeakFilter5(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 20000.0f, 0.1f, 0.1f)),
        PeakFilter6(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 20000.0f, 0.1f, 0.1f)),
        PeakFilter7(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 20000.0f, 0.1f, 0.1f)),
        PeakFilter8(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 20000.0f, 0.1f, 0.1f))
#endif
{
    juce::NormalisableRange<float> Gain35 (-15.0f, 15.0f, 0.1f);
    juce::NormalisableRange<float> Gain125 (-15.0f, 15.0f, 0.1f);
    juce::NormalisableRange<float> Gain300 (-15.0f, 15.0f, 0.1f);
    juce::NormalisableRange<float> Gain500 (-15.0f, 15.0f, 0.1f);
    juce::NormalisableRange<float> Gain1K (-15.0f, 15.0f, 0.1f);
    juce::NormalisableRange<float> Gain4K (-15.0f, 15.0f, 0.1f);
    juce::NormalisableRange<float> Gain8K (-15.0f, 15.0f, 0.1f);
    juce::NormalisableRange<float> Gain16K (-15.0f, 15.0f, 0.1f);
    
    tree.createAndAddParameter("Gain35", "35Hz", "35Hz", Gain35, 0.0f, nullptr, nullptr);
    tree.createAndAddParameter("Gain125", "125Hz", "125Hz", Gain125, 0.0f, nullptr, nullptr);
    tree.createAndAddParameter("Gain300", "300Hz", "300Hz", Gain300, 0.0f, nullptr, nullptr);
    tree.createAndAddParameter("Gain500", "500Hz", "500Hz", Gain500, 0.0f, nullptr, nullptr);
    tree.createAndAddParameter("Gain1K", "1KHz", "1KHz", Gain1K, 0.0f, nullptr, nullptr);
    tree.createAndAddParameter("Gain4K", "4KHz", "4KHz", Gain4K, 0.0f, nullptr, nullptr);
    tree.createAndAddParameter("Gain8K", "8KHz", "8KHz", Gain8K, 0.0f, nullptr, nullptr);
    tree.createAndAddParameter("Gain16K", "16KHz", "16KHz", Gain16K, 0.0f, nullptr, nullptr);
    
}
JGEQGraphicEqualizerAudioProcessor::~JGEQGraphicEqualizerAudioProcessor()
{
}
//==============================================================================

const juce::String JGEQGraphicEqualizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}
bool JGEQGraphicEqualizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}
bool JGEQGraphicEqualizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}
bool JGEQGraphicEqualizerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}
double JGEQGraphicEqualizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
int JGEQGraphicEqualizerAudioProcessor::getNumPrograms()
{
    return 1;
}
int JGEQGraphicEqualizerAudioProcessor::getCurrentProgram()
{
    return 0;
}
void JGEQGraphicEqualizerAudioProcessor::setCurrentProgram (int index)
{
    
}
const juce::String JGEQGraphicEqualizerAudioProcessor::getProgramName (int index)
{
    return {};
}
void JGEQGraphicEqualizerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    
}
//==============================================================================

void JGEQGraphicEqualizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getMainBusNumOutputChannels();
    
    PeakFilter1.prepare(spec);
    PeakFilter1.reset();
    PeakFilter2.prepare(spec);
    PeakFilter2.reset();
    PeakFilter3.prepare(spec);
    PeakFilter3.reset();
    PeakFilter4.prepare(spec);
    PeakFilter4.reset();
    PeakFilter5.prepare(spec);
    PeakFilter5.reset();
    PeakFilter6.prepare(spec);
    PeakFilter6.reset();
    PeakFilter7.prepare(spec);
    PeakFilter7.reset();
    PeakFilter8.prepare(spec);
    PeakFilter8.reset();
}
void JGEQGraphicEqualizerAudioProcessor::releaseResources()
{
}
#ifndef JucePlugin_PreferredChannelConfigurations
bool JGEQGraphicEqualizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif
    return true;
  #endif
}
#endif

void JGEQGraphicEqualizerAudioProcessor::updateFilter()
{
    float Q = 2.0f;
    float Gain35 = *tree.getRawParameterValue("Gain35");
    float Gain125 = *tree.getRawParameterValue("Gain125");
    float Gain300 = *tree.getRawParameterValue("Gain300");
    float Gain500 = *tree.getRawParameterValue("Gain500");
    float Gain1K = *tree.getRawParameterValue("Gain1K");
    float Gain4K = *tree.getRawParameterValue("Gain4K");
    float Gain8K = *tree.getRawParameterValue("Gain8K");
    float Gain16K = *tree.getRawParameterValue("Gain16K");
    
    *PeakFilter1.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, 35.0f, Q, juce::Decibels::decibelsToGain(Gain35));
    *PeakFilter2.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, 125.0f, Q, juce::Decibels::decibelsToGain(Gain125));
    *PeakFilter3.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, 300.0f, Q, juce::Decibels::decibelsToGain(Gain300));
    *PeakFilter4.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, 500.0f, Q, juce::Decibels::decibelsToGain(Gain500));
    *PeakFilter5.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, 1000.0f, Q, juce::Decibels::decibelsToGain(Gain1K));
    *PeakFilter6.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, 4000.0f, Q, juce::Decibels::decibelsToGain(Gain4K));
    *PeakFilter7.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, 8000.0f, Q, juce::Decibels::decibelsToGain(Gain8K));
    *PeakFilter8.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, 16000.0f, Q, juce::Decibels::decibelsToGain(Gain16K));
}
void JGEQGraphicEqualizerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int channel = 0; channel <totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for (int sample= 0; sample <buffer.getNumSamples(); ++sample)
        {
            channelData [sample] = channelData[sample] * juce::Decibels::decibelsToGain(mGainValue);
        }
    }
    juce::dsp::AudioBlock<float> block (buffer);
    updateFilter();
    PeakFilter1.process(juce::dsp::ProcessContextReplacing <float> (block));
    PeakFilter2.process(juce::dsp::ProcessContextReplacing <float> (block));
    PeakFilter3.process(juce::dsp::ProcessContextReplacing <float> (block));
    PeakFilter4.process(juce::dsp::ProcessContextReplacing <float> (block));
    PeakFilter5.process(juce::dsp::ProcessContextReplacing <float> (block));
    PeakFilter6.process(juce::dsp::ProcessContextReplacing <float> (block));
    PeakFilter7.process(juce::dsp::ProcessContextReplacing <float> (block));
    PeakFilter8.process(juce::dsp::ProcessContextReplacing <float> (block));
}
//==============================================================================

bool JGEQGraphicEqualizerAudioProcessor::hasEditor() const
{
    return true;
}
juce::AudioProcessorEditor* JGEQGraphicEqualizerAudioProcessor::createEditor()
{
    return new JGEQGraphicEqualizerAudioProcessorEditor (*this);
}
//==============================================================================

void JGEQGraphicEqualizerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void JGEQGraphicEqualizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JGEQGraphicEqualizerAudioProcessor();
}
//==============================================================================
