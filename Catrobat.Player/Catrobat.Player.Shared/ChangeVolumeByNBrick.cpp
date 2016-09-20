#include "pch.h"
#include "ChangeVolumeByNBrick.h"
#include "Interpreter.h"
#include "SoundManager.h"

using namespace std;
using namespace ProjectStructure;

ChangeVolumeByNBrick::ChangeVolumeByNBrick(Catrobat_Player::NativeComponent::IChangeVolumeByNBrick^ brick, Script* parent) :
	Brick(TypeOfBrick::ChangeVolumeByNBrick, parent),
	m_volumeChange(make_shared<FormulaTree>(brick->Volume))
{
}

void ChangeVolumeByNBrick::Execute()
{
	auto volume_change = Interpreter::Instance()->EvaluateFormulaToFloat(m_volumeChange, m_parent->GetParent());
	float old_volume = SoundManager::Instance()->getVolume() * 100;
	float new_volume = 0;
	if (old_volume + volume_change > 100)
	{
		new_volume = 100;
	}
	else if (old_volume + volume_change < 0)
	{
		new_volume = 0;
	}
	else
	{
		new_volume = old_volume + volume_change;
	}
	SoundManager::Instance()->setVolume(new_volume / 100);
}
