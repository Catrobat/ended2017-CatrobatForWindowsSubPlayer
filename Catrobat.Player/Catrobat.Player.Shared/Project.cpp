#include "pch.h"
#include "Project.h"
#include "Constants.h"

using namespace std;
using namespace ProjectStructure;
using namespace Catrobat_Player::NativeComponent;


Project::Project(IProject^ project) :
    m_header(make_unique<Header>(project->Header))
{
    int z_index = 0;
    for each (Catrobat_Player::NativeComponent::IObject^ object in project->Objects)
    {
        m_objectList.insert(std::pair<int, std::shared_ptr<Object> >((z_index++), make_shared<Object>(object)));
    }

    for each (Catrobat_Player::NativeComponent::IUserVariable^ userVariable in project->Variables)
    {
        m_variableList.insert(std::pair<std::string, std::shared_ptr<UserVariable>>(Helper::StdString(userVariable->Name), make_shared<UserVariable>(userVariable)));
    }
}

Project::~Project()
{
}

void Project::CheckProjectScreenSize()
{
    if (GetHeader()->GetScreenHeight() == 0 || GetHeader()->GetScreenWidth() == 0)
    {
        GetHeader()->SetDefaultScreenSize();
    }
}

void Project::SetupWindowSizeDependentResources(
    const shared_ptr<DX::DeviceResources>& deviceResources)
{
    for each (pair<int, shared_ptr<Object>> obj in m_objectList)
    {
        obj.second->SetupWindowSizeDependentResources(deviceResources);
    }
}

void Project::LoadTextures(const shared_ptr<DX::DeviceResources>& deviceResources)
{
    for each (pair<int, shared_ptr<Object>> obj in m_objectList)
    {
        obj.second->LoadTextures(deviceResources);
    }
}

void Project::StartUp()
{
    for each (pair<int, shared_ptr<Object>> obj in m_objectList)
    {
        obj.second->StartUp();
    }
}

void Project::Render(const shared_ptr<DX::DeviceResources>& deviceResources)
{
    for each (pair<int, shared_ptr<Object>> obj in m_objectList)
    {
        obj.second->Draw(deviceResources);
    }
}

shared_ptr<UserVariable> Project::GetVariable(string name)
{
    map<string, shared_ptr<UserVariable >>::iterator searchItem = m_variableList.find(name);
    if (searchItem != m_variableList.end())
        return searchItem->second;
    return NULL;
}

