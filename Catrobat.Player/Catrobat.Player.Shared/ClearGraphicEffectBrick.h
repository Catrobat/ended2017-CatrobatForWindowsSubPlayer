#pragma once

#include "Brick.h"
#include "IClearGraphicEffectBrick.h"

namespace ProjectStructure
{
    class ClearGraphicEffectBrick : public Brick
    {
    public:
        ClearGraphicEffectBrick(Catrobat_Player::NativeComponent::IClearGraphicEffectBrick^ brick, Script* parent);
        void Execute();
    };
}