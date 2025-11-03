#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

<<<<<<< HEAD

=======
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
class PlayerGUI : public juce::Component,
	public juce::Button::Listener,
	public juce::Slider::Listener,
	public juce::Timer

{
public:
	PlayerGUI();
	~PlayerGUI();

	static int numOfPlayers;
	PlayerGUI* player2;

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
	void releaseResources();

	// gui
	void paint(juce::Graphics& g) override;
	void resized() override;

<<<<<<< HEAD
	// speed
	void updateSpeed();

	// mixer 
	void addMixerInputSource(PlayerGUI& source1, PlayerGUI& source2);
	void mixerGetNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
	void mixerPrepareToPlay(int samplesPerBlockExpected, double sampleRate);

=======
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
	// Timer callback for updating progress
	void timerCallback() override;

private:
	PlayerAudio playeraudio;


	juce::TextButton loadButton{ "Load Files" };
	juce::TextButton restartButton{ "Restart" };
	juce::TextButton stopButton{ "Stop" };

	// loop button
	juce::TextButton loopButton{ "loop" };

	// segment loop button
	juce::ToggleButton segmentButton{ "segment" };

	// mute button
	juce::TextButton muteButton{ "mute" };

	// pause/end buttons
	juce::TextButton pauseButton{ "pause" };
	juce::TextButton gotoendButton{ "gotoend" };
	juce::TextButton gotostartButton{ "gotostart" };

	//volume label
	juce::Label volumeLabel;
	juce::Slider volumeSlider;

	//speed label
	juce::Slider speedSlider;
	juce::Label speedLabel;

<<<<<<< HEAD
	// add new track button
	juce::TextButton newTrackButton{ "Add new track" };

	// Segment (start point, end point) label
	juce::Label startLabel;
	juce::Label endLabel;

	// Progress slider - ADD THIS
	juce::Slider progressSlider;
	juce::Label progressLabel;

	// Segment sliders
	juce::Slider pointA;
	juce::Slider pointB;
=======
	// Progress slider - ADD THIS
	juce::Slider progressSlider;
	juce::Label progressLabel;
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946

	std::unique_ptr<juce::FileChooser> fileChooser;

	// Event
	void buttonClicked(juce::Button* button) override;
	void sliderValueChanged(juce::Slider* slider) override;

	bool keyPressed(const juce::KeyPress& key) override;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI);
};
