#include "pch.h"
#include "ChangeVariableBrick.h"
#include "FormulaTree.h"
#include "Helper.h"
#include "Interpreter.h"
#include "ProjectDaemon.h"

using namespace ProjectStructure;

ChangeVariableBrick::ChangeVariableBrick(Catrobat_Player::NativeComponent::IChangeVariableBrick^ brick, Script* parent)
    : VariableManagementBrick(TypeOfBrick::SetVariableBrick, brick, parent)
{
}

void ChangeVariableBrick::Execute()
{
    // TODO: typecheck and logic
    std::string variable_value = m_variableFormula->Value();

    // Check whether variable value refers to another variable
    std::string actual_value = Interpreter::Instance()->EvaluateVariableValue(variable_value, m_parent->GetParent());

    if (m_variableFormula->GetType() == Type::NUMBER || m_variableFormula->GetType() == Type::USER_VARIABLE)
    {
        double current;
        double to_add;

        std::shared_ptr<UserVariable> variable_local = m_parent->GetParent()->GetVariable(m_variableName);
        std::shared_ptr<UserVariable> variable_global = ProjectDaemon::Instance()->GetProject()->GetVariable(m_variableName);
        std::shared_ptr<UserVariable> variable = NULL;
        if (variable_global != NULL)
        {
            variable = variable_global;
        }
        else if (variable_local != NULL)
        {
            variable = variable_local;
        }
        else
        {
            return;
        }

        // TODO check: negative m_variable allowed?
        // TODO check expected behaviour --> e.g. what if current is no number but to_add or vice-versa?
        if (Helper::ConvertStringToDouble(variable->GetValue(), &current)
            && Helper::ConvertStringToDouble(actual_value, &to_add)
            && ((current > 0 && to_add > 0 && DBL_MAX - current >= to_add)
                || (current < 0 && to_add < 0 && DBL_MIN - current <= to_add)
                || (current > 0 && to_add < 0) || (current < 0 && to_add > 0)))
        {
            variable->SetValue(std::to_string(current + to_add));
        }
    }
}