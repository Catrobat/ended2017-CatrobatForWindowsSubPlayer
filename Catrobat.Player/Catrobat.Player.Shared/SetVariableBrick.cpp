#include "pch.h"
#include "Interpreter.h"
#include "ProjectDaemon.h"
#include "SetVariableBrick.h"

using namespace ProjectStructure;

SetVariableBrick::SetVariableBrick(Catrobat_Player::NativeComponent::ISetVariableBrick^ brick, Script* parent)
    : VariableManagementBrick(TypeOfBrick::SetVariableBrick, brick, parent)
{
}

void SetVariableBrick::Execute()
{
    // TODO: typecheck and logic
    std::string variable_name = m_variable->GetName();
    std::string variable_value = m_variableFormula->Value();

    // Check whether variable value refers to another variable
    std::string actual_value = Interpreter::Instance()->EvaluateVariableValue(variable_value, m_parent->GetParent());

    // Check whether variable is local or global, prefer local if both exist, and then set the value
    std::shared_ptr<UserVariable> variable = m_parent->GetParent()->GetVariable(variable_name);
    if (variable != NULL)
    {
        variable->SetValue(actual_value);
        return;
    }
    variable = ProjectDaemon::Instance()->GetProject()->GetVariable(variable_name);
    if (variable != NULL)
    {
        variable->SetValue(actual_value);
    }
}