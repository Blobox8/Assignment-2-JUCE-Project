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
}

MainComponent::~MainComponent()
{
    shutdownAudio();
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
    player1.setBounds(10, 10, 480, getHeight() - 20);
    player2.setBounds(510, 10, 480, getHeight() - 20);
}
