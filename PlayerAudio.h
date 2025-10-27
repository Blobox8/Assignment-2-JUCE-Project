#pragma once
#include <JuceHeader.h>

class PlayerAudio {
//hello
public:
    PlayerAudio();
    ~PlayerAudio();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    bool loadFile(const juce::File& file);

	void gotostart();
	void gotoend();

    /*void play();
    void stop();
    void setGain(float gain);
    void setPosition(double pos);
    double getPosition(double pos) const;
    double getLength() const;*/

    // toggle sound file loop
    void toggleLoop(std::unique_ptr<juce::AudioFormatReaderSource> &readersource);


    bool isLoop;
    bool isMuted;
    float lastGain;
    bool isPaused;


    

    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio);
};
