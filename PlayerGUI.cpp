
#include "PlayerGUI.h"

int PlayerGUI::numOfPlayers = 1;

PlayerGUI::PlayerGUI() :
    playlistModel(playeraudio)
{
    playlistBox.setModel(&playlistModel);
    playlistBox.setColour(juce::ListBox::backgroundColourId, juce::Colours::grey);
    addAndMakeVisible(playlistBox);

    for (auto* btn : { &loadMultiButton, &restartButton , &stopButton, &loopButton ,&muteButton,
        &pauseButton , &gotoendButton , &gotostartButton ,&nextButton ,&prevButton })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    segmentButton.addListener(this);
    addAndMakeVisible(segmentButton);

    nextButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    nextButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    prevButton.setColour(juce::TextButton::buttonColourId, juce::Colours::deepskyblue);
    prevButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    stopButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);

    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colours::orange);
    volumeSlider.setColour(juce::Slider::trackColourId, juce::Colours::white);
    volumeSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::darkgrey);

    speedSlider.setColour(juce::Slider::thumbColourId, juce::Colours::orange);
    speedSlider.setColour(juce::Slider::trackColourId, juce::Colours::white);
    speedSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::darkgrey);

    if (numOfPlayers == 1)
    {
        newTrackButton.addListener(this);
        addAndMakeVisible(newTrackButton);
    }

    volumeLabel.setText("Volume", juce::dontSendNotification);
    volumeLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    addAndMakeVisible(volumeLabel);

    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    fileInfoLabel.setText("No file loaded", juce::dontSendNotification);
    fileInfoLabel.setColour(juce::Label::textColourId, juce::Colours::cyan);
    addAndMakeVisible(fileInfoLabel);

    speedSlider.setRange(0.5, 2.0, 0.1);
    speedSlider.setValue(1.0);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    speedSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    speedSlider.addListener(this);
    addAndMakeVisible(speedSlider);

    speedLabel.setText("Speed", juce::dontSendNotification);
    addAndMakeVisible(speedLabel);

    progressSlider.setRange(0.0, 1.0, 0.01);
    progressSlider.setValue(0.0);
    progressSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    progressSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 60, 30);
    progressSlider.addListener(this);
    addAndMakeVisible(progressSlider);

    progressLabel.setText("Progress", juce::dontSendNotification);
    progressLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    addAndMakeVisible(progressLabel);

    pointA.setRange(0.00, 1.00, 0.01);
    pointB.setRange(0.00, 1.00, 0.01);
    addAndMakeVisible(pointA);
    addAndMakeVisible(pointB);

    startLabel.setText("Start", juce::dontSendNotification);
    endLabel.setText("End", juce::dontSendNotification);
    addAndMakeVisible(startLabel);
    addAndMakeVisible(endLabel);

    playeraudio.isLoop = false;
    playeraudio.isMuted = false;
    playeraudio.lastGain = 0.5f;
    playeraudio.isPaused = false;
    playeraudio.isSegmentLoop = false;

    startTimer(33);
    setWantsKeyboardFocus(true);
}

PlayerGUI::~PlayerGUI() {
    stopTimer();
}

void PlayerGUI::timerCallback()
{
    if (numOfPlayers == 2)
    {
        removeChildComponent(&newTrackButton);
        (this)->setVisible(true);
    }

    if (playeraudio.transportSource.getLengthInSeconds() > 0.0)
    {
        double currentPos = playeraudio.transportSource.getCurrentPosition();


        if (!progressSlider.isMouseButtonDown())
        {
            progressSlider.setValue(currentPos, juce::dontSendNotification);
        }
    }
    else
    {
        progressSlider.setValue(0.0, juce::dontSendNotification);
    }

    if (playeraudio.isSegmentLoop && playeraudio.isLoop)
    {
        double currentPos = playeraudio.transportSource.getCurrentPosition();
        double startPos = pointA.getValue();
        double endPos = pointB.getValue();

        if (currentPos > endPos || currentPos < startPos)
            playeraudio.transportSource.setPosition(startPos);
    }
}

void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
    g.setColour(juce::Colours::white.withAlpha(0.3f));
    g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(2), 10.0f, 2.0f);
}

void PlayerGUI::resized()
{
    int availableHeight = getHeight();
    int availableWidth = getWidth();

    // Calculat spacing based on available height
    int buttonHeight = 40;
    int smallButtonHeight = 30;
    int labelHeight = 25;
    int sliderHeight = 25;

    int y = 10;

    // First column of buttons
    int buttonSpacing = (numOfPlayers == 2) ? 70 : 100;

    loadMultiButton.setBounds(10, 10, 90, buttonHeight);
    restartButton.setBounds(10, 60, 70, buttonHeight);
    stopButton.setBounds(10, 110, 70, buttonHeight);
    loopButton.setBounds(10, 160, 70, buttonHeight);


    //y += buttonHeight + 10;

    // Second column of buttons
    pauseButton.setBounds(getWidth() - 80, 10, 70, buttonHeight);
    gotoendButton.setBounds(getWidth() - 80, 60, 70, buttonHeight);
    gotostartButton.setBounds(getWidth() - 80,110, 70, buttonHeight);
    muteButton.setBounds(getWidth() - 80, 160, 70, buttonHeight);



    y += buttonHeight + 10;

    // Navigation buttons
    prevButton.setBounds(getWidth()/2 -80, getHeight() - 120, 80, 40);
    nextButton.setBounds(getWidth() / 2 +20, getHeight() - 120, 80, 40);

    y += smallButtonHeight + 10;

    // File info
    fileInfoLabel.setBounds(10, getHeight()-150, availableWidth - 20, labelHeight);

    y += labelHeight + 10;
    segmentButton.setBounds(10, 240, 70, buttonHeight);

    // Segment controls
    startLabel.setBounds(getWidth()/2 -110, 250, 40, labelHeight);
    pointA.setBounds(getWidth() / 2 -70 , 250, 80, labelHeight);
    endLabel.setBounds(getWidth() / 2 +10, 250, 40, labelHeight);
    pointB.setBounds(getWidth() / 2  +50, 250, 80, labelHeight);

    y += labelHeight + 15;

    // Volume and speed control
    int controlWidth = (availableWidth - 30) / 2;

    volumeLabel.setBounds(10, 280, 50, labelHeight);
    volumeSlider.setBounds(65, 280, controlWidth - 60, sliderHeight);

    speedLabel.setBounds(controlWidth + 10, 280, 50, labelHeight);
    speedSlider.setBounds(controlWidth + 65, 280, controlWidth - 60, sliderHeight);

    y += sliderHeight + 15;

    // Calculate playlist height dynamically
    /*int progressSectionHeight = 60;
    int minPlaylistHeight = 80;*/

    int playlistHeight = 200;

    // Ensure minimum playlist height
   /* if (playlistHeight < minPlaylistHeight) {
        playlistHeight = minPlaylistHeight;
    }*/

    // Position playlist
    playlistBox.setBounds(10, getHeight()-350, availableWidth - 20, playlistHeight);

    y += playlistHeight + 10;

    // Progress slider
    progressLabel.setBounds(10, getHeight() - 50, 60, labelHeight);
    progressSlider.setBounds(75, getHeight() - 50, availableWidth - 90, sliderHeight);

    // New track button only for first player
    if (numOfPlayers == 1) {
        newTrackButton.setBounds(getWidth()/2 - 50, 10, 110, 30);
    }
}

bool PlayerGUI::keyPressed(const juce::KeyPress& key)
{
    if (key.getKeyCode() == juce::KeyPress::spaceKey)
    {
        pauseButton.triggerClick();
        return true;
    }
    if (key.getKeyCode() == 'm' || key.getKeyCode() == 'M')
    {
        muteButton.triggerClick();
        return true;
    }
    if (key.getKeyCode() == 's' || key.getKeyCode() == 'S')
    {
        stopButton.triggerClick();
        return true;
    }
    if (key.getKeyCode() == 'r' || key.getKeyCode() == 'R')
    {
        restartButton.triggerClick();
        return true;
    }
    if (key.getKeyCode() == 'l' || key.getKeyCode() == 'L')
    {
        loopButton.triggerClick();
        return true;
    }
    if (key.getKeyCode() == '+' || key.getKeyCode() == ']')
    {
        float currentSpeed = speedSlider.getValue();
        float newSpeed = juce::jmin(2.0f, currentSpeed + 0.1f);
        speedSlider.setValue(newSpeed);
        playeraudio.Speed(newSpeed);
        return true;
    }

    if (key.getKeyCode() == '-' || key.getKeyCode() == '[')
    {
        float currentSpeed = speedSlider.getValue();
        float newSpeed = juce::jmax(0.25f, currentSpeed - 0.1f);
        speedSlider.setValue(newSpeed);
        playeraudio.Speed(newSpeed);
        return true;
    }
    if (key.getKeyCode() == '0')
    {
        speedSlider.setValue(1.0);
        playeraudio.Speed(1.0f);
        return true;
    }
    if (key.getKeyCode() == juce::KeyPress::leftKey)
    {
        double currentPos = playeraudio.transportSource.getCurrentPosition();
        playeraudio.transportSource.setPosition(juce::jmax(0.0, currentPos - 5.0));
        return true;
    }
    if (key.getKeyCode() == juce::KeyPress::rightKey)
    {
        double currentPos = playeraudio.transportSource.getCurrentPosition();
        double totalLength = playeraudio.transportSource.getLengthInSeconds();
        playeraudio.transportSource.setPosition(juce::jmin(totalLength, currentPos + 5.0));
        return true;
    }
    if (key.getKeyCode() == juce::KeyPress::upKey)
    {
        float currentVolume = volumeSlider.getValue();
        volumeSlider.setValue(juce::jmin(1.0, currentVolume + 0.1));
        return true;
    }
    if (key.getKeyCode() == juce::KeyPress::downKey)
    {
        float currentVolume = volumeSlider.getValue();
        volumeSlider.setValue(juce::jmax(0.0, currentVolume - 0.1));
        return true;
    }
    return false;
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadMultiButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select audio files...",
            juce::File{},
            "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectMultipleItems, // FIXED: Multi-select enabled
            [this](const juce::FileChooser& fc)
            {
                auto files = fc.getResults();
                if (!files.isEmpty() && playeraudio.loadFiles(files))
                {
                    fileInfoLabel.setText(playeraudio.getDisplayInfo(), juce::dontSendNotification);
                    playlistBox.updateContent();
                    playlistBox.selectRow(playeraudio.getCurrentIndex(), true, true);

                    // Change progress slider and pointA and pointB range when a file is loaded
                    progressSlider.setRange(0.0, playeraudio.transportSource.getLengthInSeconds(), 0.01);
                    pointA.setRange(0.0, playeraudio.transportSource.getLengthInSeconds(), 0.01);
                    pointB.setRange(0.0, playeraudio.transportSource.getLengthInSeconds(), 0.01);

                }
                progressSlider.setValue(0.0);
            });
    }

    if (button == &nextButton)
    {
        playeraudio.playNext();
        fileInfoLabel.setText(playeraudio.getDisplayInfo(), juce::dontSendNotification);
        playlistBox.selectRow(playeraudio.getCurrentIndex(), true, true);
    }

    if (button == &prevButton)
    {
        playeraudio.playPrevious();
        fileInfoLabel.setText(playeraudio.getDisplayInfo(), juce::dontSendNotification);
        playlistBox.selectRow(playeraudio.getCurrentIndex(), true, true);
    }
    if (button == &restartButton)
    {
        playeraudio.transportSource.start();
    }

    if (button == &stopButton)
    {
        playeraudio.transportSource.stop();
        playeraudio.transportSource.setPosition(0.0);
        progressSlider.setValue(0.0);
    }

    if (button == &loopButton)
    {
        playeraudio.isLoop = !playeraudio.isLoop;
        if (playeraudio.isLoop)
        {
            playeraudio.toggleLoop(playeraudio.readerSource);
            loopButton.setButtonText("Looping");
        }
        else
        {
            playeraudio.toggleLoop(playeraudio.readerSource);
            loopButton.setButtonText("Loop");
        }
    }

    if (button == &segmentButton)
    {
        if (segmentButton.getToggleState())
        {
            playeraudio.isSegmentLoop = true;
        }
        else
        {
            playeraudio.isSegmentLoop = false;
        }
    }

    if (button == &muteButton)
    {
        playeraudio.isMuted = !playeraudio.isMuted;
        if (playeraudio.isMuted)
        {
            playeraudio.lastGain = playeraudio.transportSource.getGain();
            playeraudio.transportSource.setGain(0.0f);
            volumeSlider.setValue(0.0);
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
        progressSlider.setValue(0.0);
    }

    if (button == &gotoendButton)
    {
        playeraudio.gotoend();
        progressSlider.setValue(1.0);
    }

    if (button == &newTrackButton)
    {
        auto* window = findParentComponentOfClass<juce::DocumentWindow>();
        if (window != nullptr) {
            window->setSize(1000, 700);
        }
        removeChildComponent(&newTrackButton);
        numOfPlayers++;

        // Force resize of all components
        resized();
    }
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
    {
        playeraudio.transportSource.setGain((float)slider->getValue());
    }
    else if (slider == &speedSlider)
    {
        playeraudio.Speed((float)speedSlider.getValue());
    }
    else if (slider == &progressSlider)
    {
        double newPosition = progressSlider.getValue();
        playeraudio.transportSource.setPosition(newPosition);
    }
}

void PlayerGUI::addMixerInputSource(PlayerGUI& source1, PlayerGUI& source2)
{
    playeraudio.addMixerInputSource(source1.playeraudio.resamplingSource, source2.playeraudio.resamplingSource);
}

void PlayerGUI::mixerGetNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playeraudio.mixerGetNextAudioBlock(bufferToFill);
}

void PlayerGUI::mixerPrepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playeraudio.mixerPrepareToPlay(samplesPerBlockExpected, sampleRate);
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
