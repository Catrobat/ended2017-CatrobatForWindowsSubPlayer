#include "pch.h"
#include "Helper.h"
#include "VariableManagementBrick.h"

using namespace std;
using namespace ProjectStructure;

VariableManagementBrick::VariableManagementBrick(TypeOfBrick brickType, Catrobat_Player::NativeComponent::IVariableManagementBrick^ brick, Script* parent) :
    Brick(brickType, parent),
    m_variableFormula(make_shared<FormulaTree>(brick->VariableFormula))
{
    if (brick->Variable)
        m_variableName = Helper::StdString(brick->Variable->Name);
    else
        m_variableName = ""; // No variable assigned in brick
}