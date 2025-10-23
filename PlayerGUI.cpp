#include "PlayerGUI.h"
#include "PlayerAudio.h"


PlayerGUI::PlayerGUI() {

    // Add buttons
    for (auto* btn : { &loadButton, &restartButton , &stopButton, &loopButton ,&muteButton})
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

	muteButton.setButtonText("Mute");

    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    // Initialize isLoop
    playeraudio.isLoop = false;
}

PlayerGUI::~PlayerGUI() {}

void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void PlayerGUI::resized()
{
    int y = 20;
    loadButton.setBounds(20, y, 100, 40);
    restartButton.setBounds(140, y, 80, 40);
    stopButton.setBounds(240, y, 80, 40);
    loopButton.setBounds(340, y, 80, 40);
    /*prevButton.setBounds(340, y, 80, 40);
    nextButton.setBounds(440, y, 80, 40);*/

    volumeSlider.setBounds(10, 100, getWidth()/2 - 20, 30);
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        juce::FileChooser chooser("Select audio files...",
            juce::File{},
            "*.wav;*.mp3");

        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...",
            juce::File{},
            "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                playeraudio.loadFile(file);
            });
    }

    if (button == &restartButton)
    {
        playeraudio.transportSource.start();
    }

    if (button == &stopButton)
    {
        playeraudio.transportSource.stop();
        playeraudio.transportSource.setPosition(0.0);
    }

    if (button == &loopButton)
    {
        playeraudio.isLoop = !(playeraudio.isLoop);
        playeraudio.toggleLoop(playeraudio.readerSource);
    }
   
    

}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playeraudio.transportSource.setGain((float)slider->getValue());
}


void PlayerGUI::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playeraudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerGUI::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) 
{
    playeraudio.getNextAudioBlock(bufferToFill);
}

void PlayerGUI::releaseResources() 
{
    playeraudio.releaseResources();
}

