#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

<<<<<<< HEAD

=======
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
	// mo فئة مساعدة لتوفير بيانات قائمة التشغيل للـ ListBox
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

		// إذا كان هذا هو الملف الذي يتم تشغيله حالياً
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
			playerAudio.loadFile(row); // تحميل وتشغيل الملف المحدد
			// ⚠️ نستخدم repaint لتحديث تحديد الملف
			// ملاحظة: في بيئة حقيقية قد نحتاج لـ MessageManager::callAsync أو Timer
			// لكن هنا نكتفي بالـ repaint
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

    // mo تغيير اسم زر التحميل ليعكس وظيفته الجديدة (تحميل عدة ملفات)
    juce::TextButton loadMultiButton{ "Load Files" };

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

    // mo زرا التحكم في قائمة التشغيل
    juce::TextButton nextButton{ "Next" };
    juce::TextButton prevButton{ "Prev" };
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
      // mo لافتة جديدة لعرض معلومات الملف
    juce::Label fileInfoLabel;
     // mo مكوّنات قائمة التشغيل
    juce::ListBox playlistBox;
   PlaylistComponent playlistModel;

	std::unique_ptr<juce::FileChooser> fileChooser;

	// Event
	void buttonClicked(juce::Button* button) override;
	void sliderValueChanged(juce::Slider* slider) override;

	bool keyPressed(const juce::KeyPress& key) override;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI);
};

