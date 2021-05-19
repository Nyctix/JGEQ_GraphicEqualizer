//==============================================================================
#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
class JGEQGraphicEqualizerAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                  public juce::Slider::Listener
{
public:
    JGEQGraphicEqualizerAudioProcessorEditor (JGEQGraphicEqualizerAudioProcessor&);
    ~JGEQGraphicEqualizerAudioProcessorEditor() override;
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* slider) override;

private:
    juce::Slider mGainDial;
    juce::Slider m35HzDial;
    juce::Slider m125HzDial;
    juce::Slider m300HzDial;
    juce::Slider m500HzDial;
    juce::Slider m1KHzDial;
    juce::Slider m4KHzDial;
    juce::Slider m8KHzDial;
    juce::Slider m16KHzDial;
    
    juce::Label mGainLabel;
    juce::Label m35HzLabel;
    juce::Label m125HzLabel;
    juce::Label m300HzLabel;
    juce::Label m500HzLabel;
    juce::Label m1KHzLabel;
    juce::Label m4KHzLabel;
    juce::Label m8KHzLabel;
    juce::Label m16KHzLabel;
    juce::Label JGEQLabel;
    
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> m35HzValue;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> m125HzValue;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> m300HzValue;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> m500HzValue;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> m1KHzValue;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> m4KHzValue;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> m8KHzValue;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> m16KHzValue;
    
    JGEQGraphicEqualizerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JGEQGraphicEqualizerAudioProcessorEditor)
};
//==============================================================================
