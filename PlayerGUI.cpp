#include "PlayerGUI.h"
#include "PlayerAudio.h"


PlayerGUI::PlayerGUI() {

    // add timer
    startTimer(1); // the timer 

    // Add buttons
    for (auto* btn : { &loadButton, &restartButton , &stopButton, &loopButton ,&muteButton, &pauseButton , &gotoendButton , &gotostartButton })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

	muteButton.setButtonText("Mute");

    //volume label
	volumeLabel.setText("Volume", juce::dontSendNotification);
	volumeLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
	addAndMakeVisible(volumeLabel);

    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
	volumeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    //volumeSlider.setColour(juce::Slider::LinearBar, juce::Colours::skyblue);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    

	

    // Initialize variables for loopButton
    playeraudio.isLoop = false;

    // initialize variables for muteButton
    playeraudio.isMuted = false;
    playeraudio.lastGain = 0.5f;

    // initialize variables for pauseButton
    playeraudio.isPaused = false;

    // initialize variables for posSlider
    isMoved = false;
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
    y = 70;
	pauseButton.setBounds(20, y, 100, 40);
	gotoendButton.setBounds(140, y, 80, 40);
	gotostartButton.setBounds(240, y, 80, 40);
	muteButton.setBounds(340,y, 80, 40);

    /*prevButton.setBounds(340, y, 80, 40);
    nextButton.setBounds(440, y, 80, 40);*/


	volumeLabel.setBounds(1, 120, 56, 30);

    volumeSlider.setBounds(60, 120, getWidth()/2 - 50, 30);

    posSlider.setBounds(60, 150, getWidth() / 2 - 5, 20);
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

                // add position slider when file is loaded
                posSlider.setRange(0, playeraudio.transportSource.getLengthInSeconds(), 0.01);
                posSlider.setValue(0);
                posSlider.addListener(this);
                addAndMakeVisible(posSlider);

                // check if posSlider is being moved
                posSlider.onDragStart = [this]() {
                    isMoved = true;
                    };
                posSlider.onDragEnd = [this]() {
                    isMoved = false;
                    };

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
    
    if (button == &muteButton)
    {
        playeraudio.isMuted = !playeraudio.isMuted;
        if (playeraudio.isMuted)
        {
            playeraudio.lastGain = playeraudio.transportSource.getGain();
            playeraudio.transportSource.setGain(0.0f);
            volumeSlider.setValue(0.0);//
            muteButton.setButtonText("Unmute");
            muteButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
        }
        else
        {
            playeraudio.transportSource.setGain(playeraudio.lastGain);
            muteButton.setButtonText("Mute");
            volumeSlider.setValue(playeraudio.lastGain);
            muteButton.setColour(juce::TextButton::buttonColourId, getLookAndFeel().findColour(juce::TextButton::buttonColourId));
        }
    }

    if (button == &pauseButton) 
    {
        if (playeraudio.isPaused)
        {
            playeraudio.transportSource.start();
            pauseButton.setButtonText("Pause");
        }
        else
        {
            playeraudio.transportSource.stop();
            pauseButton.setButtonText("Resume");
        }

        playeraudio.isPaused = !playeraudio.isPaused;
    }
	if (button == &gotostartButton)
	{
		playeraudio.gotostart();
	}

	if (button == &gotoendButton)
	{
		playeraudio.gotoend();
	}

}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playeraudio.transportSource.setGain((float)slider->getValue());

    if (isMoved && slider == &posSlider) // check if the slider is being moved by the user
        playeraudio.transportSource.setPosition(posSlider.getValue());
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

void PlayerGUI::timerCallback() 
{   
    if (playeraudio.transportSource.isPlaying()) {
        // update posSlider value
        posSlider.setValue(playeraudio.transportSource.getCurrentPosition());
    }
}
