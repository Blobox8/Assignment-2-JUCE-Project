#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"


class PlayerGUI : public juce::Component, 
	public juce::Button::Listener, 
	public juce::Slider::Listener,
	public juce::Timer
{
public:
	PlayerGUI();
	~PlayerGUI();

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
	void releaseResources();

	// timer
	void timerCallback() override;

	// gui
	void paint(juce::Graphics& g) override;
	void resized() override;

	

private:
	PlayerAudio playeraudio;


	juce::TextButton loadButton{ "Load Files" };
	juce::TextButton restartButton{ "Restart" };
	juce::TextButton stopButton{ "Stop" };

	// loop button
	juce::TextButton loopButton{ "loop" };

	// mute button
	juce::TextButton muteButton{ "mute" };

	// pause/end buttons
	juce::TextButton pauseButton{ "pause" };
	juce::TextButton toEndButton{ "to end" };

	// segment loop toggle button
	juce::ToggleButton segmentButton{ "segment loop" };

 
	juce::TextButton gotoendButton{ "gotoend" };
	juce::TextButton gotostartButton{ "gotostart" };

	juce::Label volumeLabel;
	juce::Slider volumeSlider;
	juce::Slider posSlider;
	juce::Slider segA, segB;

	std::unique_ptr<juce::FileChooser> fileChooser;


	bool isMoved;

	// Event
	void buttonClicked(juce::Button* button) override;
	void sliderValueChanged(juce::Slider* slider) override;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI);
};
