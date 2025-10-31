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

	// gui
	void paint(juce::Graphics& g) override;
	void resized() override;

	// Timer callback for updating progress
	void timerCallback() override;

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
	juce::TextButton gotoendButton{ "gotoend" };
	juce::TextButton gotostartButton{ "gotostart" };

	//volume label
	juce::Label volumeLabel;
	juce::Slider volumeSlider;

	//speed label
	juce::Slider speedSlider;
	juce::Label speedLabel;

	// Progress slider - ADD THIS
	juce::Slider progressSlider;
	juce::Label progressLabel;

	std::unique_ptr<juce::FileChooser> fileChooser;

	// Event
	void buttonClicked(juce::Button* button) override;
	void sliderValueChanged(juce::Slider* slider) override;

	bool keyPressed(const juce::KeyPress& key) override;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI);
};
