#include "pch.h"
#include "ChangeTransparencyByNBrick.h"
#include "Script.h"
#include "Object.h"
#include "Interpreter.h"

using namespace ProjectStructure;
using namespace std;

ChangeTransparencyByNBrick::ChangeTransparencyByNBrick(Catrobat_Player::NativeComponent::IChangeTransparencyByNBrick^ brick, Script* parent) :
    Brick(TypeOfBrick::ChangeTransparencyByNBrick, parent),
    m_transparency(make_shared<FormulaTree>(brick->Transparency))
{
}

void ChangeTransparencyByNBrick::Execute()
{
    m_parent->GetParent()->SetTransparency(m_parent->GetParent()->GetTransparency() +
        (Interpreter::Instance()->EvaluateFormulaToFloat(m_transparency, GetParent()->GetParent()) / 100.f));
}