#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlaylistComponent : public juce::ListBoxModel
{
public:
    PlaylistComponent(PlayerAudio& pa) : playerAudio(pa) {}
    int getNumRows() override { return playerAudio.getPlaylistSize(); }

    void paintListBoxItem(int rowNumber, juce::Graphics& g,
        int width, int height, bool rowIsSelected) override
    {
        if (rowIsSelected)
            g.fillAll(juce::Colours::cyan.withAlpha(0.3f));

        if (rowNumber == playerAudio.getCurrentIndex())
            g.setColour(juce::Colours::yellow);
        else
            g.setColour(juce::Colours::whitesmoke);

        g.drawText(playerAudio.getFileName(rowNumber),
            5, 0, width - 10, height,
            juce::Justification::centredLeft, true);
    }

    void listBoxItemClicked(int row, const juce::MouseEvent& e) override
    {
        if (row >= 0 && row < playerAudio.getPlaylistSize())
        {
            playerAudio.loadFile(row);
            if (auto* parent = dynamic_cast<juce::Component*>(this))
                parent->repaint();
        }
    }

private:
    PlayerAudio& playerAudio;
};

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

    void paint(juce::Graphics& g) override;
    void resized() override;

    void updateSpeed();

    void addMixerInputSource(PlayerGUI& source1, PlayerGUI& source2);
    void mixerGetNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void mixerPrepareToPlay(int samplesPerBlockExpected, double sampleRate);

    void timerCallback() override;

private:
    PlayerAudio playeraudio;

    juce::TextButton loadMultiButton{ "Load Files" };
    juce::TextButton restartButton{ "Restart" };
    juce::TextButton stopButton{ "Stop" };
    juce::TextButton loopButton{ "loop" };
    juce::ToggleButton segmentButton{ "segment" };
    juce::TextButton muteButton{ "mute" };
    juce::TextButton pauseButton{ "pause" };
    juce::TextButton gotoendButton{ "gotoend" };
    juce::TextButton gotostartButton{ "gotostart" };
    juce::TextButton nextButton{ "Next" };
    juce::TextButton prevButton{ "Prev" };
    juce::TextButton newTrackButton{ "Add new track" };

    juce::Label volumeLabel;
    juce::Slider volumeSlider;
    juce::Slider speedSlider;
    juce::Label speedLabel;
    juce::Label startLabel;
    juce::Label endLabel;
    juce::Slider pointA;
    juce::Slider pointB;
    juce::Slider progressSlider;
    juce::Label progressLabel;
    juce::Label fileInfoLabel;

    juce::ListBox playlistBox;
    PlaylistComponent playlistModel;

    std::unique_ptr<juce::FileChooser> fileChooser;

    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    bool keyPressed(const juce::KeyPress& key) override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI);
};
