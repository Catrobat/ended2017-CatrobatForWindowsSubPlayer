#pragma once

#include "Brick.h"
#include "IComeToFrontBrick.h"

namespace ProjectStructure
{
    class ComeToFrontBrick : public Brick
    {
    public:
        ComeToFrontBrick(Catrobat_Player::NativeComponent::IComeToFrontBrick^ brick, Script* parent);
        void Execute();
    };
}
