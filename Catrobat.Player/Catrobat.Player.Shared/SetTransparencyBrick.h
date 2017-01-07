#pragma once

#include "Brick.h"
#include "ISetTransparencyBrick.h"

namespace ProjectStructure
{
    class SetTransparencyBrick :
        public Brick
    {
    public:
        SetTransparencyBrick(Catrobat_Player::NativeComponent::ISetTransparencyBrick^ brick, Script* parent);
        void Execute();
    private:
        std::shared_ptr<FormulaTree> m_transparency;
    };
}