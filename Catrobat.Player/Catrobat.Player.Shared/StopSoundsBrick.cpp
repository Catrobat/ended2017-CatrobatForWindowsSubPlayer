#include "pch.h"
#include "StopSoundsBrick.h"
#include "Interpreter.h"
#include "SoundManager.h"

using namespace std;
using namespace ProjectStructure;

StopSoundsBrick::StopSoundsBrick(Catrobat_Player::NativeComponent::IStopSoundsBrick^ brick, Script* parent) :
	Brick(TypeOfBrick::StopSoundsBrick, parent)
{
}

void StopSoundsBrick::Execute()
{
	SoundManager::Instance()->stopAllSounds();
}
