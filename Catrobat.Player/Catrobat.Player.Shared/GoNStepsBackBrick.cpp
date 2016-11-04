#include "pch.h"
#include "GoNStepsBackBrick.h"
#include "Interpreter.h"
#include "Object.h"
#include "ProjectDaemon.h"
#include "Script.h"

using namespace ProjectStructure;

GoNStepsBackBrick::GoNStepsBackBrick(Catrobat_Player::NativeComponent::IGoNStepsBackBrick^ brick, Script* parent) :
    Brick(TypeOfBrick::GoNStepsBackBrick, parent), m_Steps(std::make_shared<FormulaTree>(brick->Steps))
{
}

void GoNStepsBackBrick::Execute()
{
    int steps = Interpreter::Instance()->EvaluateFormulaToInt(m_Steps, m_parent->GetParent());
    if (steps == 0)
    {
        return;
    }

    std::map<int, std::shared_ptr<Object>> objects = ProjectDaemon::Instance()->GetProject()->GetObjectList();
    unsigned z_index_of_obj = 0;
    std::shared_ptr<Object> obj;
    for each (std::pair<int, std::shared_ptr<Object>> current_obj in objects)
    {
        if (current_obj.second->GetName() == m_parent->GetParent()->GetName())
        {
            z_index_of_obj = current_obj.first;
            obj = current_obj.second;
            break;
        }
    }

    int new_z_index = z_index_of_obj - steps;
    if (new_z_index < 0)
    {
        new_z_index = 0;
    }
    if (new_z_index >= objects.size())
    {
        new_z_index = objects.size() - 1;
    }

    if (steps > 0)
    {
        for (unsigned z_index = z_index_of_obj; z_index > new_z_index; z_index--)
        {
            objects[z_index] = objects[z_index - 1];
        }
    }
    else
    {
        for (unsigned z_index = z_index_of_obj; z_index < new_z_index; z_index++)
        {
            objects[z_index] = objects[z_index + 1];
        }
    }
    objects[new_z_index] = obj;
    ProjectDaemon::Instance()->GetProject()->SetObjectList(objects);
}