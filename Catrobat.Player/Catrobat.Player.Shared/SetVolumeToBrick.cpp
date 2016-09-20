#include "pch.h"
#include "SetVolumeToBrick.h"
#include "Interpreter.h"
#include "SoundManager.h"

using namespace std;
using namespace ProjectStructure;

SetVolumeToBrick::SetVolumeToBrick(Catrobat_Player::NativeComponent::ISetVolumeToBrick^ brick, Script* parent) :
	Brick(TypeOfBrick::SetVolumeToBrick, parent),
	m_volume(make_shared<FormulaTree>(brick->Volume))
{
}

void SetVolumeToBrick::Execute()
{
	auto volume = Interpreter::Instance()->EvaluateFormulaToFloat(m_volume, m_parent->GetParent());
	if (volume < 0 || volume > 100)
	{
		return;
	}
	SoundManager::Instance()->setVolume(volume / 100);
}
