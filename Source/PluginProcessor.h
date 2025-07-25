#pragma once

#include <JuceHeader.h>

//==============================================================================
class DelayAudioProcessor : public juce::AudioProcessor
{
public:
    DelayAudioProcessor();
    ~DelayAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

private:
    juce::AudioBuffer<float> delayBuffer;
    int writePosition = 0;

    double lastSampleRate = 44100.0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayAudioProcessor)
};

// /*
//  ==============================================================================
//
//    This file contains the basic framework code for a JUCE plugin processor.
//
//  ==============================================================================
//*/
//
//#pragma once
//
//#include <JuceHeader.h>
//
////==============================================================================
///**
//*/
//class DelayAudioProcessor  : public juce::AudioProcessor
//{
//public:
//    //==============================================================================
//    DelayAudioProcessor();
//    ~DelayAudioProcessor() override;
//
//    //==============================================================================
//    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
//    void releaseResources() override;
//
//   #ifndef JucePlugin_PreferredChannelConfigurations
//    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
//   #endif
//
//    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
//
//    //==============================================================================
//    juce::AudioProcessorEditor* createEditor() override;
//    bool hasEditor() const override;
//
//    //==============================================================================
//    const juce::String getName() const override;
//
//    bool acceptsMidi() const override;
//    bool producesMidi() const override;
//    bool isMidiEffect() const override;
//    double getTailLengthSeconds() const override;
//
//    //==============================================================================
//    int getNumPrograms() override;
//    int getCurrentProgram() override;
//    void setCurrentProgram (int index) override;
//    const juce::String getProgramName (int index) override;
//    void changeProgramName (int index, const juce::String& newName) override;
//
//    //==============================================================================
//    void getStateInformation (juce::MemoryBlock& destData) override;
//    void setStateInformation (const void* data, int sizeInBytes) override;
//
//    float delayTimeMs = 500.0f;
//    float feedback = 0.5f;
//    float mix = 0.5f;
//
//    juce::AudioProcessorValueTreeState apvts;
//
//
//private:
//    juce::AudioBuffer<float> delayBuffer;
//    int writePosition = 0;
//
//    double lastSampleRate = 44100.0;
//
//    //==============================================================================
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessor)
//};
