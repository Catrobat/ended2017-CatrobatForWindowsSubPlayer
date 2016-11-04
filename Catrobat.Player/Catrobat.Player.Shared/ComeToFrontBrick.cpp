#include "pch.h"
#include "ComeToFrontBrick.h"
#include "Script.h"
#include "Object.h"
#include "ProjectDaemon.h"

using namespace ProjectStructure;

ComeToFrontBrick::ComeToFrontBrick(Catrobat_Player::NativeComponent::IComeToFrontBrick^ brick, Script* parent) : Brick(TypeOfBrick::ComeToFrontBrick, parent)
{
}

void ComeToFrontBrick::Execute()
{
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
    for (unsigned z_index = z_index_of_obj; z_index < objects.size() - 1; z_index++)
    {
        objects[z_index] = objects[z_index + 1];
    }
    objects[objects.size() - 1] = obj;
    ProjectDaemon::Instance()->GetProject()->SetObjectList(objects);
}