#pragma once

#include "ContainerBrick.h"
#include "Object.h"
#include "IRepeatBrick.h"

#include <condition_variable>
#include <list>

namespace ProjectStructure
{
    class RepeatBrick :
        public ContainerBrick
    {
    public:
        RepeatBrick(Catrobat_Player::NativeComponent::IRepeatBrick^ brick, Script* parent);
        ~RepeatBrick();

        void Execute();
        void Stop();
    private:
        std::shared_ptr<FormulaTree> m_timesToRepeat;
        bool m_stop;
        std::condition_variable m_cv;
        std::mutex m_mutex;
    };
}