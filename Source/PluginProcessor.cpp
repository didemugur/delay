#include "PluginProcessor.h"
#include "PluginEditor.h"

DelayAudioProcessor::DelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
}

DelayAudioProcessor::~DelayAudioProcessor() {}

const juce::String DelayAudioProcessor::getName() const { return JucePlugin_Name; }
bool DelayAudioProcessor::acceptsMidi() const { return false; }
bool DelayAudioProcessor::producesMidi() const { return false; }
bool DelayAudioProcessor::isMidiEffect() const { return false; }
double DelayAudioProcessor::getTailLengthSeconds() const { return 2.0; }

int DelayAudioProcessor::getNumPrograms() { return 1; }
int DelayAudioProcessor::getCurrentProgram() { return 0; }
void DelayAudioProcessor::setCurrentProgram(int) {}
const juce::String DelayAudioProcessor::getProgramName(int) { return {}; }
void DelayAudioProcessor::changeProgramName(int, const juce::String&) {}

void DelayAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;

    int delayBufferSize = (int)(2.0 * sampleRate); // max 2 sec
    delayBuffer.setSize(getTotalNumInputChannels(), delayBufferSize);
    delayBuffer.clear();
    writePosition = 0;
}

void DelayAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DelayAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}
#endif

void DelayAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    const float delayTimeMs = apvts.getRawParameterValue("DELAYTIME")->load();
    const float feedback = apvts.getRawParameterValue("FEEDBACK")->load();
    const float mix = apvts.getRawParameterValue("MIX")->load();

    const int numInputChannels = getTotalNumInputChannels();
    const int numSamples = buffer.getNumSamples();
    const int delayBufferSize = delayBuffer.getNumSamples();

    for (int channel = 0; channel < numInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        auto* delayData = delayBuffer.getWritePointer(channel);

        int readPosition = (writePosition + delayBufferSize - (int)(lastSampleRate * (delayTimeMs / 1000.0f))) % delayBufferSize;

        for (int i = 0; i < numSamples; ++i)
        {
            float in = channelData[i];
            float delayed = delayData[readPosition];

            channelData[i] = in * (1.0f - mix) + delayed * mix;

            delayData[writePosition] = in + delayed * feedback;

            if (++writePosition >= delayBufferSize)
                writePosition = 0;
            if (++readPosition >= delayBufferSize)
                readPosition = 0;
        }
    }
}

juce::AudioProcessorEditor* DelayAudioProcessor::createEditor()
{
    return new DelayAudioProcessorEditor(*this);
}

bool DelayAudioProcessor::hasEditor() const { return true; }

void DelayAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void DelayAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    juce::ValueTree tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid())
        apvts.state = tree;
}

juce::AudioProcessorValueTreeState::ParameterLayout DelayAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("DELAYTIME", "Delay Time", 1.0f, 2000.0f, 500.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FEEDBACK", "Feedback", 0.0f, 0.95f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MIX", "Mix", 0.0f, 1.0f, 0.5f));

    return { params.begin(), params.end() };
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DelayAudioProcessor();
}

/*
//  ==============================================================================
//
//    This file contains the basic framework code for a JUCE plugin processor.
//
//  ==============================================================================
//*/
//
//#include "PluginProcessor.h"
//#include "PluginEditor.h"
//
////==============================================================================
//DelayAudioProcessor::DelayAudioProcessor()
//#ifndef JucePlugin_PreferredChannelConfigurations
//     : AudioProcessor (BusesProperties()
//                     #if ! JucePlugin_IsMidiEffect
//                      #if ! JucePlugin_IsSynth
//                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
//                      #endif
//                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
//                     #endif
//                       )
//#endif
//{
//}
//
//DelayAudioProcessor::~DelayAudioProcessor()
//{
//}
//
////==============================================================================
//const juce::String DelayAudioProcessor::getName() const
//{
//    return JucePlugin_Name;
//}
//
//bool DelayAudioProcessor::acceptsMidi() const
//{
//   #if JucePlugin_WantsMidiInput
//    return true;
//   #else
//    return false;
//   #endif
//}
//
//bool DelayAudioProcessor::producesMidi() const
//{
//   #if JucePlugin_ProducesMidiOutput
//    return true;
//   #else
//    return false;
//   #endif
//}
//
//bool DelayAudioProcessor::isMidiEffect() const
//{
//   #if JucePlugin_IsMidiEffect
//    return true;
//   #else
//    return false;
//   #endif
//}
//
//double DelayAudioProcessor::getTailLengthSeconds() const
//{
//    return 2.0;
//}
//
//int DelayAudioProcessor::getNumPrograms()
//{
//    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
//                // so this should be at least 1, even if you're not really implementing programs.
//}
//
//int DelayAudioProcessor::getCurrentProgram()
//{
//    return 0;
//}
//
//void DelayAudioProcessor::setCurrentProgram (int index)
//{
//}
//
//const juce::String DelayAudioProcessor::getProgramName (int index)
//{
//    return {};
//}
//
//void DelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
//{
//}
//
////==============================================================================
//void DelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
//{
//    lastSampleRate = sampleRate;
//
//    int delayBufferSize = (int)(2.0 * sampleRate); // max 2 sec
//    delayBuffer.setSize(getTotalNumInputChannels(), delayBufferSize);
//    delayBuffer.clear();
//    writePosition = 0;
//}
//
//void DelayAudioProcessor::releaseResources()
//{
//    
//}
//
//#ifndef JucePlugin_PreferredChannelConfigurations
//bool DelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
//{
//  #if JucePlugin_IsMidiEffect
//    juce::ignoreUnused (layouts);
//    return true;
//  #else
//    // This is the place where you check if the layout is supported.
//    // In this template code we only support mono or stereo.
//    // Some plugin hosts, such as certain GarageBand versions, will only
//    // load plugins that support stereo bus layouts.
//    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
//     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
//        return false;
//
//    // This checks if the input layout matches the output layout
//   #if ! JucePlugin_IsSynth
//    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
//        return false;
//   #endif
//
//    return true;
//  #endif
//}
//#endif
//
//void DelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
//{
//    juce::ScopedNoDenormals noDenormals;
//    auto totalNumInputChannels  = getTotalNumInputChannels();
//    auto totalNumOutputChannels = getTotalNumOutputChannels();
//
//    const int numInputChannels = getTotalNumInputChannels();
//    const int numSamples = buffer.getNumSamples();
//    const int delayBufferSize = delayBuffer.getNumSamples();
//    
//    /*for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
//        buffer.clear (i, 0, buffer.getNumSamples());*/
//
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);
//
//		auto* delayData = delayBuffer.getWritePointer(channel);
//        int readPosition = (writePosition + delayBufferSize - (int)(lastSampleRate * (delayTimeMs / 1000.0f))) % delayBufferSize;
//
//        for (int i = 0; i < numSamples; ++i)
//        {
//            float in = channelData[i];
//            float delayed = delayData[readPosition];
//
//            channelData[i] = in * (1.0f - mix) + delayed * mix;
//
//            delayData[writePosition] = in + delayed * feedback;
//
//            if (++writePosition >= delayBufferSize)
//                writePosition = 0;
//            if (++readPosition >= delayBufferSize)
//                readPosition = 0;
//        }
//    }
//}
//
//
////==============================================================================
//bool DelayAudioProcessor::hasEditor() const
//{
//    return true; // (change this to false if you choose to not supply an editor)
//}
//
//juce::AudioProcessorEditor* DelayAudioProcessor::createEditor()
//{
//    return new DelayAudioProcessorEditor (*this);
//}
//
////==============================================================================
//void DelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
//{
//    // You should use this method to store your parameters in the memory block.
//    // You could do that either as raw data, or use the XML or ValueTree classes
//    // as intermediaries to make it easy to save and load complex data.
//}
//
//void DelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
//{
//    // You should use this method to restore your parameters from this memory block,
//    // whose contents will have been created by the getStateInformation() call.
//}
//
////==============================================================================
//// This creates new instances of the plugin..
//juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
//{
//    return new DelayAudioProcessor();
//}
