#include "PlayerGUI.h"
#include "PlayerAudio.h"

<<<<<<< HEAD
int PlayerGUI::numOfPlayers = 1;

PlayerGUI::PlayerGUI() :
// mo 
 playlistModel(playeraudio) 
{

// mo إعداد الـ ListBox
playlistBox.setModel(&playlistModel);
playlistBox.setColour(juce::ListBox::backgroundColourId, juce::Colours::grey);
addAndMakeVisible(playlistBox);

	// Add buttons
	for (auto* btn : {  &loadMultiButton, &restartButton , &stopButton, &loopButton ,&muteButton, 
		&pauseButton , &gotoendButton , &gotostartButton ,&nextButton ,&prevButton})
	{
		btn->addListener(this);
		addAndMakeVisible(btn);
=======
PlayerGUI::PlayerGUI() {
	// Add buttons
	for (auto* btn : { &loadButton, &restartButton , &stopButton, &loopButton ,&muteButton, &pauseButton , &gotoendButton , &gotostartButton })
	{
		btn->addListener(this);
		addAndMakeVisible(btn);
		
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
	}

	// add segmentButton individually because it has a differnet type (ToggleButton)
	segmentButton.addListener(this);
	addAndMakeVisible(segmentButton);

<<<<<<< HEAD
	// add newTrackButton if there is only one player
	if (numOfPlayers == 1)
	{
		newTrackButton.addListener(this);
		addAndMakeVisible(newTrackButton);
	}
	
	// Volume label
=======
	//volume label
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
	volumeLabel.setText("Volume", juce::dontSendNotification);
	volumeLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
	addAndMakeVisible(volumeLabel);

	// Volume slider
	volumeSlider.setRange(0.0, 1.0, 0.01);
	volumeSlider.setValue(0.5);
	volumeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
	volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	volumeSlider.addListener(this);
	addAndMakeVisible(volumeSlider);
    // mo إعداد لافتة معلومات الملف
fileInfoLabel.setText("No file loaded", juce::dontSendNotification);
fileInfoLabel.setColour(juce::Label::textColourId, juce::Colours::cyan); // لون مميز
addAndMakeVisible(fileInfoLabel);
<<<<<<< HEAD
	// Speed slider
=======
	//speed slider
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
	speedSlider.setRange(0.5, 2.0, 0.1);
	speedSlider.setValue(1.0);
	speedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
	speedSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	speedSlider.addListener(this);
	addAndMakeVisible(speedSlider);
<<<<<<< HEAD

	// Speed label
	speedLabel.setText("Speed", juce::dontSendNotification);
	addAndMakeVisible(speedLabel);

	// Progress slider
	progressSlider.setRange(0.0, 1.0, 0.01);
	progressSlider.setValue(0.0);
	progressSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	progressSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 60,30);
	progressSlider.addListener(this);
	addAndMakeVisible(progressSlider);

	//Progress label
	progressLabel.setText("Progress", juce::dontSendNotification);
	progressLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
	addAndMakeVisible(progressLabel);

	// Segment sliders
	pointA.setRange(0.00, 1.00, 0.01);
	pointB.setRange(0.00, 1.00, 0.01);
	addAndMakeVisible(pointA);
	addAndMakeVisible(pointB);

	// Segment label
	startLabel.setText("Start", juce::dontSendNotification);
	endLabel.setText("End", juce::dontSendNotification);
	addAndMakeVisible(startLabel);
	addAndMakeVisible(endLabel);

	
	playeraudio.isLoop = false;
	playeraudio.isMuted = false;
	playeraudio.lastGain = 0.5f;
	playeraudio.isPaused = false;
	playeraudio.isSegmentLoop = false;

=======
	//speed label
	speedLabel.setText("Speed", juce::dontSendNotification);
	addAndMakeVisible(speedLabel);

	// Progress slider
	progressSlider.setRange(0.0, 1.0, 0.01);
	progressSlider.setValue(0.0);
	progressSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	progressSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 60,30);
	progressSlider.addListener(this);
	addAndMakeVisible(progressSlider);
	//Progress label
	progressLabel.setText("Progress", juce::dontSendNotification);
	progressLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
	addAndMakeVisible(progressLabel);

	
	playeraudio.isLoop = false;
	playeraudio.isMuted = false;
	playeraudio.lastGain = 0.5f;
	playeraudio.isPaused = false;

>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
	startTimer(33); // update every 30ms
	setWantsKeyboardFocus(true);
}

PlayerGUI::~PlayerGUI() {
	stopTimer(); // Stop timer
}

void PlayerGUI::timerCallback()
{
<<<<<<< HEAD
	// if newTackButton was pressed, make this component visible
	if (numOfPlayers == 2) 
	{
		removeChildComponent(&newTrackButton);
		(this)->setVisible(true);
	}
		

=======
	
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
	if (playeraudio.transportSource.getLengthInSeconds() > 0.0)
	{
		double currentPos = playeraudio.transportSource.getCurrentPosition();
		double totalLength = playeraudio.transportSource.getLengthInSeconds();
		double progress = currentPos / totalLength;

		
		if (!progressSlider.isMouseButtonDown())//update if no dragging 
		{
			progressSlider.setValue(progress, juce::dontSendNotification);
		}
	}
	else
	{
		progressSlider.setValue(0.0, juce::dontSendNotification);//if no sound set value to zero
	}
<<<<<<< HEAD

	if (playeraudio.isSegmentLoop && playeraudio.isLoop)
	{
		double currentPos = playeraudio.transportSource.getCurrentPosition();
		double totalLength = playeraudio.transportSource.getLengthInSeconds();
		double startPos = pointA.getValue()*totalLength;
		double endPos = pointB.getValue()*totalLength;

		if (currentPos > endPos || currentPos < startPos)
			playeraudio.transportSource.setPosition(startPos);
	}
=======
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
}

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
<<<<<<< HEAD
	segmentButton.setBounds(440, y, 80, 40);

=======
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946

	y = 70;
	pauseButton.setBounds(20, y, 100, 40);
	gotoendButton.setBounds(140, y, 80, 40);
	gotostartButton.setBounds(240, y, 80, 40);
	muteButton.setBounds(340, y, 80, 40);
    //mo تحديد موقع لافتة معلومات الملف ً
   fileInfoLabel.setBounds(10, 160, getWidth() - 20, 30);
   y = 120;
   prevButton.setBounds(10, y, 80, 30);
   nextButton.setBounds(90, y, 80, 30);

<<<<<<< HEAD

	int sliderwidth = 160;

=======
	int sliderwidth = 160;

>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
	// Volume controls
	volumeLabel.setBounds(10, 120, 50, 25);
	volumeSlider.setBounds(65, 120, sliderwidth, 25);

	// Speed controls
	speedLabel.setBounds(230, 120, 50, 25);
	speedSlider.setBounds(285, 120, sliderwidth, 25);

	// Progress slider
	progressLabel.setBounds(10, 250, 60, 25);
	progressSlider.setBounds(75, 250, getWidth() - 90, 25);
<<<<<<< HEAD

	// Segment controls
	pointA.setBounds(20, 150, 100, 25);
	pointB.setBounds(20, 170, 100, 25);
	startLabel.setBounds(120, 150, 100, 25);
	endLabel.setBounds(120, 170, 100, 25);

	newTrackButton.setBounds(20, 300, 100, 40);
=======
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
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
	if (button == &loadButton)
	{
		/*juce::FileChooser chooser("Select audio files...",
			juce::File{},
			"*.wav;*.mp3");*/

		fileChooser = std::make_unique<juce::FileChooser>(
			"Select an audio file...",
			juce::File{},
			"*.wav;*.mp3");

		fileChooser->launchAsync(
			juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
			[this](const juce::FileChooser& fc)
			{
				 auto files = fc.getResults(); // 🔄 نحصل على قائمة النتائج
                 if (!files.isEmpty() && playeraudio.loadFiles(files))
				{
					//mo
					    fileInfoLabel.setText(playeraudio.getDisplayInfo(), juce::dontSendNotification);
                        playlistBox.updateContent(); // 🆕 تحديث عرض القائمة
                        playlistBox.selectRow(playeraudio.getCurrentIndex(), true, true); // تحديد الملف الأول
                 }
					// Reset progress when new file is loaded
					progressSlider.setValue(0.0);
				}
			});
	}
     // mo م زر التالي
if (button == &nextButton)
{
    playeraudio.playNext();
    fileInfoLabel.setText(playeraudio.getDisplayInfo(), juce::dontSendNotification);
    playlistBox.selectRow(playeraudio.getCurrentIndex(), true, true);
}

// mo م زر السابق
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

<<<<<<< HEAD
	if (button == &segmentButton)
	{	
		// segment loop implementation is in PlayerGUI::timerCallback()
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

=======
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

>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
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
<<<<<<< HEAD

	if (button == &newTrackButton)
	{
		auto* window = findParentComponentOfClass<juce::DocumentWindow>();
		window->setSize(600, 600);
		removeChildComponent(&newTrackButton); // remove the button after being used
		numOfPlayers++;
	}
=======
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
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
		double newPosition = progressSlider.getValue() * playeraudio.transportSource.getLengthInSeconds();//get persentage * total seconds
		playeraudio.transportSource.setPosition(newPosition);
	}
<<<<<<< HEAD
}


// Mixer
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
=======
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
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


