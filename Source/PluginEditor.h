#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
class DelayAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    DelayAudioProcessorEditor(DelayAudioProcessor&);
    ~DelayAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    DelayAudioProcessor& audioProcessor;

    juce::Slider delayTimeSlider;
    juce::Slider feedbackSlider;
    juce::Slider mixSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayTimeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayAudioProcessorEditor)
};

//
//#pragma once
//
//#include <JuceHeader.h>
//#include "PluginProcessor.h"
//
////==============================================================================
///**
//*/
//class DelayAudioProcessorEditor  : public juce::AudioProcessorEditor
//{
//public:
//    DelayAudioProcessorEditor (DelayAudioProcessor&);
//    ~DelayAudioProcessorEditor() override;
//
//    //==============================================================================
//    void paint (juce::Graphics&) override;
//    void resized() override;
//
//private:
//    // This reference is provided as a quick way for your editor to
//    // access the processor object that created it.
//    DelayAudioProcessor& audioProcessor;
//
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessorEditor)
//};
