#include "pch.h"
#include "SetTransparencyBrick.h"
#include "Script.h"
#include "Object.h"
#include "Interpreter.h"

using namespace ProjectStructure;
using namespace std;

SetTransparencyBrick::SetTransparencyBrick(Catrobat_Player::NativeComponent::ISetTransparencyBrick^ brick, Script* parent) :
    Brick(TypeOfBrick::SetTransparencyBrick, parent),
    m_transparency(make_shared<FormulaTree>(brick->Transparency))
{
}

void SetTransparencyBrick::Execute()
{
    m_parent->GetParent()->SetTransparency((Interpreter::Instance()->EvaluateFormulaToFloat(m_transparency, GetParent()->GetParent()) / 100.0f));
}