#pragma once

#include "Brick.h"
#include "ISetVolumeToBrick.h"

namespace ProjectStructure
{
    class SetVolumeToBrick : public Brick
    {
    public:
        SetVolumeToBrick(Catrobat_Player::NativeComponent::ISetVolumeToBrick^ brick, Script* parent);
        void Execute();

    private:
        std::shared_ptr<FormulaTree> m_volume;
    };
}
