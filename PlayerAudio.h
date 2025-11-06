#pragma once
#include <JuceHeader.h>

class PlayerAudio {
public:
    PlayerAudio();
    ~PlayerAudio();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    bool loadFiles(const juce::Array<juce::File>& files);
    bool loadFile(int index);

    void playNext();
    void playPrevious();

    void gotostart();
    void gotoend();
    int getPlaylistSize() const { return playlistFiles.size(); }
    int getCurrentIndex() const { return currentFileIndex; }
    juce::String getFileName(int index) const;
    void Speed(float speed);

    void addMixerInputSource(juce::ResamplingAudioSource& source1, juce::ResamplingAudioSource& source2);
    void mixerGetNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void mixerPrepareToPlay(int samplesPerBlockExpected, double sampleRate);

    void toggleLoop(std::unique_ptr<juce::AudioFormatReaderSource>& readersource);
    juce::String getDisplayInfo() const { return displayInfo; }

    juce::ResamplingAudioSource resamplingSource;
    double currentSampleRate;

    bool isLoop;
    bool isMuted;
    float lastGain;
    bool isPaused;
    bool isSegmentLoop;

    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::MixerAudioSource mixer;

    juce::Array<juce::File> playlistFiles;
    int currentFileIndex = -1;
    juce::String displayInfo;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio);
};
