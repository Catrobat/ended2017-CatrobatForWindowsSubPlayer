#pragma once

#include "Brick.h"
#include "IChangeTransparencyByNBrick.h"

namespace ProjectStructure
{
    class ChangeTransparencyByNBrick :
        public Brick
    {
    public:
        ChangeTransparencyByNBrick(Catrobat_Player::NativeComponent::IChangeTransparencyByNBrick^ brick, Script* parent);
        void Execute();
    private:
        std::shared_ptr<FormulaTree> m_transparency;
    };
}