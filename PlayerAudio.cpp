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

bool PlayerAudio::loadFile(const juce::File& file) {
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
			


            return true;
        }
    }
    return false;
}
