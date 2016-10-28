#pragma once

#include "Object.h"
#include "UserVariable.h"
#include "IProject.h"
#include "Helper.h"
#include "Header.h"

#include <vector>

namespace ProjectStructure
{
    class Project
    {
    public:
        Project(Catrobat_Player::NativeComponent::IProject^ project);
        ~Project();

        void CheckProjectScreenSize();
        void SetupWindowSizeDependentResources(const std::shared_ptr<DX::DeviceResources>& deviceResources);
        void LoadTextures(const std::shared_ptr<DX::DeviceResources>& deviceResources);
        void StartUp();
        void Render(const std::shared_ptr<DX::DeviceResources>& deviceResources);
        std::shared_ptr<UserVariable> GetVariable(std::string name);

        std::unique_ptr<Header> const & GetHeader() { return m_header; }
        std::map<int, std::shared_ptr<Object> > GetObjectList() { return m_objectList; }
		void SetObjectList(std::map<int, std::shared_ptr<Object>> object_list) { m_objectList = object_list; }

    private:
        std::unique_ptr<Header> m_header;
        std::map<int, std::shared_ptr<Object> > m_objectList;
        std::map<std::string, std::shared_ptr<UserVariable> > m_variableList;
    };
}