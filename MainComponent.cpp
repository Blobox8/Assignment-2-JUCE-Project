#include "MainComponent.h"
#include "PlayerAudio.h"
#include "PlayerGUI.h"

MainComponent::MainComponent()
{
    addAndMakeVisible(player1);
    addChildComponent(player2);

    player1.addMixerInputSource(player1, player2);

    setSize(500, 250);
    setAudioChannels(0, 2);

    
    
        backgroundImage = juce::Image(juce::Image::RGB, 1, 2, true);
        juce::Graphics g(backgroundImage);
        g.setGradientFill(juce::ColourGradient(
            juce::Colours::darkblue, 0, 0,
            juce::Colours::black, 0, 1, false));
        g.fillAll();
    
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}


void MainComponent::paint(juce::Graphics& g)
{
   
    if (!backgroundImage.isNull())
    {
        g.drawImage(backgroundImage, getLocalBounds().toFloat());
    }
    else
    {
        g.fillAll(juce::Colours::darkgrey);
    }
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    player1.mixerPrepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    player1.mixerGetNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player1.releaseResources();
    player2.releaseResources();
}

void MainComponent::resized()
{
    
    player1.setBounds(10, 10, 485, getHeight() - 20);
    player2.setBounds(505, 10, 485, getHeight() - 20);
 
}
