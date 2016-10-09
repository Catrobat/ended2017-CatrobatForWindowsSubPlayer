#include "pch.h"
#include "Helper.h"
#include "ProjectDaemon.h"
#include "RiffReader.h"
#include "SoundManager.h"
#include "VoiceCallback.h"

using Windows::Storage::Streams::IBuffer;
using namespace ProjectStructure;

SoundManager *SoundManager::__instance = nullptr;

SoundManager::SoundManager()
{
	// Create xAudio engine and the mastering voice
	IXAudio2 *xAudio_raw; // Always raw pointers for the XAUDIO object creation, then make the shared pointer manage the pointer
	HRESULT hr = XAudio2Create(&xAudio_raw);
	xAudio.reset(xAudio_raw, [](IXAudio2 *xAudio_ptr){ xAudio_ptr->Release(); });
	if (hr != S_OK)
	{
		return;
	}
	IXAudio2MasteringVoice *mastering_voice_raw;
	hr = xAudio->CreateMasteringVoice(&mastering_voice_raw);
	masteringVoice.reset(mastering_voice_raw, [](IXAudio2MasteringVoice *mastering_voice_ptr){ mastering_voice_ptr->DestroyVoice(); });
	if (hr != S_OK)
	{
		return;
	}

	xAudio->StartEngine();
}

SoundManager::~SoundManager()
{
}

SoundManager *SoundManager::Instance()
{
	// Singleton
	if (!__instance)
	{
		__instance = new SoundManager();
	}
	return __instance;
}

void SoundManager::deleteInstance()
{
	if (__instance)
	{
	    delete __instance;
	}
	__instance = NULL;
}

bool SoundManager::Play(string fileName)
{
	// Convert string because CreateFile2 needs LCPWSTR
	string path = ProjectDaemon::Instance()->GetProjectPath() + "\\sounds\\" + fileName;
	wstring wstr = Helper::ConvertStringToLPCWSTR(path);
	LPCWSTR fileNameConverted = wstr.c_str();
	// Open exisiting file and create handle
	HANDLE fileHandle = CreateFile2(fileNameConverted, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, NULL);
	HRESULT hr = HRESULT_FROM_WIN32(GetLastError());
	if(hr != S_OK)
	{
		return false;
	}
	// RiffReader to read audio file and fill the audio buffer and waveformat
	unique_ptr<RiffReader> riffReader = make_unique<RiffReader>();
	if(!riffReader.get())
	{
		CloseHandle(fileHandle);
		return false;
	}
	WAVEFORMATEX wfx;
	std::unique_ptr<XAUDIO2_BUFFER> xAudioBuffer = riffReader->Read(fileHandle, &wfx);
	CloseHandle(fileHandle); // Need to handle?
	if(!xAudioBuffer.get())
	{
		return false;
	}
	
	// Create voice in correct format, link to master voice and submit buffer
	IXAudio2SourceVoice *voice_raw;
	VoiceCallback callback;
	hr = xAudio->CreateSourceVoice(&voice_raw, &wfx, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &callback);
	shared_ptr<IXAudio2SourceVoice> voice(voice_raw, [](IXAudio2SourceVoice* voice_ptr) { voice_ptr->DestroyVoice(); });
	if(hr != S_OK)
	{
		delete xAudioBuffer.get()->pAudioData;
		return false;
	}
	hr = voice->SubmitSourceBuffer(xAudioBuffer.get());
	if(hr != S_OK)
	{
		delete xAudioBuffer.get()->pAudioData;
		return false;
	}
	int sound_map_index = 0;
	runningVoicesMutex.lock();
	for (int sound_map_index_counter = 0; sound_map_index_counter < 100000; sound_map_index_counter++)
	{
		if (runningVoices.count(sound_map_index_counter) == 0)
		{
			runningVoices[sound_map_index_counter] = voice;
			sound_map_index = sound_map_index_counter;
			break;
		}
	}
	runningVoicesMutex.unlock();
	// Start the voice, then delete
	hr = voice->Start(0);
	WaitForSingleObjectEx(callback.hBufferEndEvent, 180000, true);
	runningVoicesMutex.lock();
	runningVoices.erase(runningVoices.find(sound_map_index));
	runningVoicesMutex.unlock();
	return (hr == S_OK);
}

shared_ptr<IXAudio2> SoundManager::getXAudio()
{
	return xAudio;
}

shared_ptr<IXAudio2MasteringVoice> SoundManager::getMasteringVoice()
{
	return masteringVoice;
}

void SoundManager::stopAllSounds()
{
    runningVoicesMutex.lock();
    for (map<int, shared_ptr<IXAudio2SourceVoice>>::iterator it = runningVoices.begin(); it != runningVoices.end(); it++)
    {
        it->second->Stop();
    }
    runningVoicesMutex.unlock();
}

float SoundManager::getVolume()
{
	return volume;
}

void SoundManager::setVolume(float new_volume)
{
	volume = new_volume;
	masteringVoice->SetVolume(new_volume);
}