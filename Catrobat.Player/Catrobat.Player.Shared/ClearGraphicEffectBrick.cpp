#include "pch.h"
#include "ClearGraphicEffectBrick.h"
#include "Script.h"
#include "Object.h"
#include "ProjectDaemon.h"

using namespace ProjectStructure;

ClearGraphicEffectBrick::ClearGraphicEffectBrick(Catrobat_Player::NativeComponent::IClearGraphicEffectBrick^ brick, Script* parent) : Brick(TypeOfBrick::ClearGraphicEffectBrick, parent)
{
}

void ClearGraphicEffectBrick::Execute()
{
    m_parent->GetParent()->SetTransparency(0.0f);
}