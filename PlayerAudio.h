#pragma once
#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h> 



class PlayerAudio {
//hello
public:
    PlayerAudio();
    ~PlayerAudio();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    // mo تغيير: دالة لتحميل عدة ملفات
    bool loadFiles(const juce::Array<juce::File>& files);
    //mo دالة لتحميل ملف معين من القائمة
    bool loadFile(int index);
    //bool loadFile(const juce::File& file);
   
    // moدوال التحكم في القائمة
    void playNext();
    void playPrevious();
	
    void gotostart();
	void gotoend();
    void Speed(float speed);
<<<<<<< HEAD

    // mixer
    void addMixerInputSource(juce::ResamplingAudioSource& source1, juce::ResamplingAudioSource& source2);
    void mixerGetNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void mixerPrepareToPlay(int samplesPerBlockExpected, double sampleRate);

=======
>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
    /*void play();
    void stop();
    void setGain(float gain);
    void setPosition(double pos);
    double getPosition(double pos) const;
    double getLength() const;*/

    // toggle sound file loop
    void toggleLoop(std::unique_ptr<juce::AudioFormatReaderSource> &readersource);
     // mo دالة جديدة للوصول إلى displayInfo
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
    juce::MixerAudioSource mixer; // used to play two tracks 
      // mo قائمة الملفات ومؤشر الملف الحالي
    juce::Array<juce::File> playlistFiles;
    int currentFileIndex = -1; // -1 يعني لا يوجد ملف محمل حاليh
    juce::String displayInfo;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio);
};

