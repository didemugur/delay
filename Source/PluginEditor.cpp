#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayAudioProcessorEditor::DelayAudioProcessorEditor(DelayAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    delayTimeSlider.setSliderStyle(juce::Slider::Rotary);
    delayTimeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(delayTimeSlider);

    feedbackSlider.setSliderStyle(juce::Slider::Rotary);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(feedbackSlider);

    mixSlider.setSliderStyle(juce::Slider::Rotary);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(mixSlider);

    delayTimeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DELAYTIME", delayTimeSlider);
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FEEDBACK", feedbackSlider);
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX", mixSlider);

    setSize(400, 200);
}

DelayAudioProcessorEditor::~DelayAudioProcessorEditor() {}

void DelayAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Simple Delay", getLocalBounds(), juce::Justification::topLeft, 1);
}

void DelayAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    auto sliderWidth = 100;
    auto sliderHeight = 100;

    delayTimeSlider.setBounds(20, 50, sliderWidth, sliderHeight);
    feedbackSlider.setBounds(140, 50, sliderWidth, sliderHeight);
    mixSlider.setBounds(260, 50, sliderWidth, sliderHeight);
}


//#include "PluginProcessor.h"
//#include "PluginEditor.h"
//
////==============================================================================
//DelayAudioProcessorEditor::DelayAudioProcessorEditor (DelayAudioProcessor& p)
//    : AudioProcessorEditor (&p), audioProcessor (p)
//{
//    // Make sure that before the constructor has finished, you've set the
//    // editor's size to whatever you need it to be.
//    setSize (400, 300);
//}
//
//DelayAudioProcessorEditor::~DelayAudioProcessorEditor()
//{
//}
//
////==============================================================================
//void DelayAudioProcessorEditor::paint (juce::Graphics& g)
//{
//    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
//
//    g.setColour (juce::Colours::white);
//    g.setFont (juce::FontOptions (15.0f));
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
//}
//
//void DelayAudioProcessorEditor::resized()
//{
//    // This is generally where you'll want to lay out the positions of any
//    // subcomponents in your editor..
//}
