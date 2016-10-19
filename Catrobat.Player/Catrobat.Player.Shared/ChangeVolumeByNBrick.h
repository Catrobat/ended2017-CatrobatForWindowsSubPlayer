#pragma once

#include "Brick.h"
#include "IChangeVolumeByNBrick.h"

namespace ProjectStructure
{
    class ChangeVolumeByNBrick : public Brick
    {
    public:
        ChangeVolumeByNBrick(Catrobat_Player::NativeComponent::IChangeVolumeByNBrick^ brick, Script* parent);
        void Execute();

    private:
        std::shared_ptr<FormulaTree> m_volumeChange;
    };
}
