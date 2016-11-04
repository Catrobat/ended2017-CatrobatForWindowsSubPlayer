#pragma once

#include "Brick.h"
#include "IGoNStepsBackBrick.h"

namespace ProjectStructure
{
    class GoNStepsBackBrick : public Brick
    {
        public:
            GoNStepsBackBrick(Catrobat_Player::NativeComponent::IGoNStepsBackBrick^ brick, Script* parent);
            void Execute();
        private:
            std::shared_ptr<FormulaTree> m_Steps;
    };
}
