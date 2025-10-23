#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"


class PlayerGUI : public juce::Component, 
	public juce::Button::Listener, 
	public juce::Slider::Listener 
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

	

private:
	PlayerAudio playeraudio;

	juce::TextButton loadButton{ "Load Files" };
	juce::TextButton restartButton{ "Restart" };
	juce::TextButton stopButton{ "Stop" };

	// loop button
	juce::TextButton loopButton{ "loop" };
	juce::TextButton muteButton{ "mute" };
	bool isMuted = false;
	float lastGain = 0.5f;


	juce::Slider volumeSlider;

	std::unique_ptr<juce::FileChooser> fileChooser;

	// Event
	void buttonClicked(juce::Button* button) override;
	void sliderValueChanged(juce::Slider* slider) override;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI);
};
