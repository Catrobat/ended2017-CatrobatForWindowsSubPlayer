#pragma once

#include "pch.h"
#include <xaudio2.h>
#include <mutex>

using namespace std;

class SoundManager
{
  private:
	static SoundManager *__instance; // shared pointer?
	shared_ptr<IXAudio2> xAudio;
	shared_ptr<IXAudio2MasteringVoice> masteringVoice;
	map<int, shared_ptr<IXAudio2SourceVoice>> runningVoices;
	mutex runningVoicesMutex;
	float volume;
  public:
	SoundManager();
	~SoundManager();
	static SoundManager *Instance();
	static void deleteInstance();
	bool Play(string fileName);
	shared_ptr<IXAudio2> getXAudio();
	shared_ptr<IXAudio2MasteringVoice> getMasteringVoice();
	void stopAllSounds();
	float getVolume();
	void setVolume(float new_volume);
};