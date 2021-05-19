//==============================================================================
#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================

JGEQGraphicEqualizerAudioProcessorEditor::JGEQGraphicEqualizerAudioProcessorEditor
(JGEQGraphicEqualizerAudioProcessor& p) : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (200, 200);
    
    mGainDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mGainDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    mGainDial.setPopupMenuEnabled(true);
    mGainDial.setRange(-48.0f, 12.0f, 0.1f);
    mGainDial.setValue(0.0f);
    mGainDial.setTextValueSuffix("dB");
    mGainDial.setNumDecimalPlacesToDisplay(1);
    mGainDial.addListener(this);
    addAndMakeVisible(mGainDial);
    mGainLabel.setText("Gain", juce::dontSendNotification);
    addAndMakeVisible(mGainLabel);
    
    m35HzDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m35HzDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    m35HzDial.setPopupMenuEnabled(true);
    m35HzDial.setTextValueSuffix("dB");
    m35HzValue = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.tree, "Gain35", m35HzDial);
    addAndMakeVisible(m35HzDial);
    m35HzLabel.setText("35Hz", juce::dontSendNotification);
    addAndMakeVisible(m35HzLabel);
    
    m125HzDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m125HzDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    m125HzDial.setPopupMenuEnabled(true);
    m125HzDial.setTextValueSuffix("dB");
    m125HzValue = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.tree, "Gain125", m125HzDial);
    addAndMakeVisible(m125HzDial);
    m125HzLabel.setText("125Hz", juce::dontSendNotification);
    addAndMakeVisible(m125HzLabel);
    
    m300HzDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m300HzDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    m300HzDial.setPopupMenuEnabled(true);
    m300HzDial.setTextValueSuffix("dB");
    m300HzValue = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.tree, "Gain300", m300HzDial);
    addAndMakeVisible(m300HzDial);
    m300HzLabel.setText("300Hz", juce::dontSendNotification);
    addAndMakeVisible(m300HzLabel);
    
    m500HzDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m500HzDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    m500HzDial.setPopupMenuEnabled(true);
    m500HzDial.setTextValueSuffix("dB");
    m500HzValue = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.tree, "Gain500", m500HzDial);
    addAndMakeVisible(m500HzDial);
    m500HzLabel.setText("500Hz", juce::dontSendNotification);
    addAndMakeVisible(m500HzLabel);
    
    m1KHzDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m1KHzDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    m1KHzDial.setPopupMenuEnabled(true);
    m1KHzDial.setTextValueSuffix("dB");
    m1KHzValue = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.tree, "Gain1K", m1KHzDial);
    addAndMakeVisible(m1KHzDial);
    m1KHzLabel.setText("1KHz", juce::dontSendNotification);
    addAndMakeVisible(m1KHzLabel);
    
    m4KHzDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m4KHzDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    m4KHzDial.setPopupMenuEnabled(true);
    m4KHzDial.setTextValueSuffix("dB");
    m4KHzValue = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.tree, "Gain4K", m4KHzDial);
    addAndMakeVisible(m4KHzDial);
    m4KHzLabel.setText("4KHz", juce::dontSendNotification);
    addAndMakeVisible(m4KHzLabel);
    
    m8KHzDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m8KHzDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    m8KHzDial.setPopupMenuEnabled(true);
    m8KHzDial.setTextValueSuffix("dB");
    m8KHzValue = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.tree, "Gain8K", m8KHzDial);
    addAndMakeVisible(m8KHzDial);
    m8KHzLabel.setText("8KHz", juce::dontSendNotification);
    addAndMakeVisible(m8KHzLabel);
    
    m16KHzDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m16KHzDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    m16KHzDial.setPopupMenuEnabled(true);
    m16KHzDial.setTextValueSuffix("dB");
    m16KHzValue = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.tree, "Gain16K", m16KHzDial);
    addAndMakeVisible(m16KHzDial);
    m16KHzLabel.setText("16KHz", juce::dontSendNotification);
    addAndMakeVisible(m16KHzLabel);
    
    addAndMakeVisible(JGEQLabel);
    JGEQLabel.setText("J-GEQ Graphic Equalizer", juce::dontSendNotification);
    
    setSize(1475, 300);
    setResizeLimits(1475, 300, 1475, 300);
}
JGEQGraphicEqualizerAudioProcessorEditor::~JGEQGraphicEqualizerAudioProcessorEditor()
{
}
//==============================================================================

void JGEQGraphicEqualizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
}

void JGEQGraphicEqualizerAudioProcessorEditor::resized()
{
    mGainDial.setBounds(50, getHeight()/2 - 75, 150, 150);
    m35HzDial.setBounds(200, getHeight()/2 - 75, 150, 150);
    m125HzDial.setBounds(350, getHeight()/2 - 75, 150, 150);
    m300HzDial.setBounds(500, getHeight()/2 - 75, 150, 150);
    m500HzDial.setBounds(650, getHeight()/2 - 75, 150, 150);
    m1KHzDial.setBounds(800, getHeight()/2 - 75, 150, 150);
    m4KHzDial.setBounds(950, getHeight()/2 - 75, 150, 150);
    m8KHzDial.setBounds(1100, getHeight()/2 - 75, 150, 150);
    m16KHzDial.setBounds(1250, getHeight()/2 - 75, 150, 150);
    
    mGainLabel.setBounds(100, getHeight()/2, 50, 20);
    m35HzLabel.setBounds(250, getHeight()/2, 50, 20);
    m125HzLabel.setBounds(400, getHeight()/2, 50, 20);
    m300HzLabel.setBounds(550, getHeight()/2, 50, 20);
    m500HzLabel.setBounds(700, getHeight()/2, 50, 20);
    m1KHzLabel.setBounds(850, getHeight()/2, 50, 20);
    m4KHzLabel.setBounds(1000, getHeight()/2, 50, 20);
    m8KHzLabel.setBounds(1150, getHeight()/2, 50, 20);
    m16KHzLabel.setBounds(1300, getHeight()/2, 50, 20);
    
    JGEQLabel.setBounds(30, 10, 280, 60);
}

void JGEQGraphicEqualizerAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &mGainDial)
    {
        audioProcessor.mGainValue = mGainDial.getValue();
    }
}
//==============================================================================
