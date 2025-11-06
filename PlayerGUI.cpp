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
        double totalLength = playeraudio.transportSource.getLengthInSeconds();
        double progress = currentPos / totalLength;

        if (!progressSlider.isMouseButtonDown())
        {
            progressSlider.setValue(progress, juce::dontSendNotification);
        }
    }
    else
    {
        progressSlider.setValue(0.0, juce::dontSendNotification);
    }

    if (playeraudio.isSegmentLoop && playeraudio.isLoop)
    {
        double currentPos = playeraudio.transportSource.getCurrentPosition();
        double totalLength = playeraudio.transportSource.getLengthInSeconds();
        double startPos = pointA.getValue() * totalLength;
        double endPos = pointB.getValue() * totalLength;

        if (currentPos > endPos || currentPos < startPos)
            playeraudio.transportSource.setPosition(startPos);
    }
}

void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void PlayerGUI::resized()
{
    int availableHeight = getHeight();
    int availableWidth = getWidth();

    // Calculate dynamic spacing based on available height
    int buttonHeight = 40;
    int smallButtonHeight = 30;
    int labelHeight = 25;
    int sliderHeight = 25;

    int y = 10;

    // First row of buttons - adjust spacing for two players
    int buttonSpacing = (numOfPlayers == 2) ? 70 : 100; // Closer spacing for two players

    loadMultiButton.setBounds(10, y, 90, buttonHeight);
    restartButton.setBounds(110, y, 70, buttonHeight);
    stopButton.setBounds(190, y, 70, buttonHeight);
    loopButton.setBounds(270, y, 70, buttonHeight);
    segmentButton.setBounds(350, y, 70, buttonHeight);

    y += buttonHeight + 10;

    // Second row of buttons
    pauseButton.setBounds(10, y, 90, buttonHeight);
    gotoendButton.setBounds(110, y, 70, buttonHeight);
    gotostartButton.setBounds(190, y, 70, buttonHeight);
    muteButton.setBounds(270, y, 70, buttonHeight);

    y += buttonHeight + 10;

    // Navigation buttons
    prevButton.setBounds(10, y, 80, smallButtonHeight);
    nextButton.setBounds(100, y, 80, smallButtonHeight);

    y += smallButtonHeight + 10;

    // File info
    fileInfoLabel.setBounds(10, y, availableWidth - 20, labelHeight);

    y += labelHeight + 10;

    // Segment controls - position them more compactly
    startLabel.setBounds(10, y, 40, labelHeight);
    pointA.setBounds(55, y, 80, labelHeight);
    endLabel.setBounds(145, y, 40, labelHeight);
    pointB.setBounds(190, y, 80, labelHeight);

    y += labelHeight + 15;

    // Volume and speed controls - side by side but compact
    int controlWidth = (availableWidth - 30) / 2;

    volumeLabel.setBounds(10, y, 50, labelHeight);
    volumeSlider.setBounds(65, y, controlWidth - 60, sliderHeight);

    speedLabel.setBounds(controlWidth + 10, y, 50, labelHeight);
    speedSlider.setBounds(controlWidth + 65, y, controlWidth - 60, sliderHeight);

    y += sliderHeight + 15;

    // Calculate playlist height dynamically
    int progressSectionHeight = 60;
    int minPlaylistHeight = 80;

    int playlistHeight = availableHeight - y - progressSectionHeight;

    // Ensure minimum playlist height
    if (playlistHeight < minPlaylistHeight) {
        playlistHeight = minPlaylistHeight;
    }

    // Position playlist
    playlistBox.setBounds(10, y, availableWidth - 20, playlistHeight);

    y += playlistHeight + 10;

    // Progress slider at the bottom
    progressLabel.setBounds(10, y, 60, labelHeight);
    progressSlider.setBounds(75, y, availableWidth - 90, sliderHeight);

    // New track button only for first player, positioned appropriately
    if (numOfPlayers == 1) {
        newTrackButton.setBounds(availableWidth - 120, 10, 110, 30);
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
            window->setSize(900, 700); // Wider window for two players
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
        double newPosition = progressSlider.getValue() * playeraudio.transportSource.getLengthInSeconds();
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
