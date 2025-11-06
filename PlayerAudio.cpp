#include "PlayerAudio.h"

// constructor
PlayerAudio::PlayerAudio() :resamplingSource(&transportSource,false){
    formatManager.registerBasicFormats();
    resamplingSource.setResamplingRatio(1.0);
}

// destructor
PlayerAudio::~PlayerAudio() {
    transportSource.setSource(nullptr);
}

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    currentSampleRate = sampleRate;
    resamplingSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    //transportSource.getNextAudioBlock(bufferToFill);
    resamplingSource.getNextAudioBlock(bufferToFill);
}

void PlayerAudio::releaseResources()
{
    transportSource.releaseResources();
    resamplingSource.releaseResources();
}
void PlayerAudio::Speed(float speed)
{
	resamplingSource.setResamplingRatio(speed/1.0);
}
void PlayerAudio::toggleLoop(std::unique_ptr<juce::AudioFormatReaderSource> &readersource) {
    readersource->setLooping(isLoop);
}
void PlayerAudio::gotostart()
{
	transportSource.setPosition(0.0);
}

void PlayerAudio::gotoend()
{
	double length = transportSource.getLengthInSeconds();

	if (length > 0.0)
		transportSource.setPosition(length);
}
// mo تنفيذ دالة للحصول على اسم الملف
juce::String PlayerAudio::getFileName(int index) const
{
    if (index >= 0 && index < playlistFiles.size())
        return playlistFiles[index].getFileNameWithoutExtension();
    return {};
}
void PlayerAudio::addMixerInputSource(juce::ResamplingAudioSource& source1, juce::ResamplingAudioSource& source2)
{
    mixer.addInputSource(&source1, false);
    mixer.addInputSource(&source2, false);
}

void PlayerAudio::mixerGetNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixer.getNextAudioBlock(bufferToFill);
}

void PlayerAudio::mixerPrepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    mixer.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

// mo تنفيذ دالة تحميل ملف معين من القائمة
bool PlayerAudio::loadFile(int index) {
    if (index < 0 || index >= playlistFiles.size())
        return false;
     const juce::File& file = playlistFiles[index];

	
    if (file.existsAsFile())
    {
        if (auto* reader = formatManager.createReaderFor(file))
        {
            // 🔑 Disconnect old source first
            transportSource.stop();
            transportSource.setSource(nullptr);
            readerSource.reset();

            // Create new reader source
            readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
            
            // Attach safely
            transportSource.setSource(readerSource.get(),
                0,
                nullptr,
                reader->sampleRate);
            transportSource.start();
			// mo تحديث مؤشر الملف الحال
			 currentFileIndex = index;
			//mo منطق استخراج وعرض البيانات
            juce::String title = reader->metadataValues["title"].isNotEmpty() ? reader->metadataValues["title"] : file.getFileName();
            juce::String author = reader->metadataValues["artist"].isNotEmpty() ? reader->metadataValues["artist"] : "";
            double duration = transportSource.getLengthInSeconds();
            juce::String durationString = juce::String::formatted("%.2f s", duration);

            displayInfo = title;
            if (author.isNotEmpty())
            {
                displayInfo << " by " << author;
            }
            displayInfo << " (" << durationString << ")";

            return true;
        }
    }
    displayInfo = "Failed to load file.";
    return false;
}
<<<<<<< HEAD
=======


>>>>>>> d7e4cfe81c88bc1af3c7d0569311734ca54c1946
/*return true;
        }
    }
    return false;
}*/
//mo دالة تحميل الملفات المتعددة
bool PlayerAudio::loadFiles(const juce::Array<juce::File>& files) {
    if (files.isEmpty())
        return false;

    playlistFiles = files; // حفظ القائمة الجديدة
    currentFileIndex = -1; // إعادة تعيين المؤشر
    return loadFile(0); // تحميل الملف الأول مباشرة
}


// mo دالة التشغيل التالي
void PlayerAudio::playNext() {
    if (playlistFiles.size() > 1) {
        int nextIndex = (currentFileIndex + 1) % playlistFiles.size(); // دوران (Loop)
        loadFile(nextIndex);
    }
}

// mo دالة التشغيل السابق
void PlayerAudio::playPrevious() {
    if (playlistFiles.size() > 1) {
        int prevIndex = currentFileIndex - 1;
        if (prevIndex < 0)
            prevIndex = playlistFiles.size() - 1; // دوران (Loop)
        loadFile(prevIndex);
    }
}

