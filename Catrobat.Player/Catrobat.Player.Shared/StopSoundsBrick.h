#pragma once

#include "Brick.h"
#include "IStopSoundsBrick.h"

namespace ProjectStructure
{
    class StopSoundsBrick : public Brick
    {
    public:
        StopSoundsBrick(Catrobat_Player::NativeComponent::IStopSoundsBrick^ brick, Script* parent);
        void Execute();
    };
}
