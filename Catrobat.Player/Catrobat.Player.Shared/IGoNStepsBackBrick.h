#pragma once

#include "IBrick.h"

namespace Catrobat_Player
{
    namespace NativeComponent
    {
        public interface class IGoNStepsBackBrick : public IBrick
        {
            public:
                virtual property IFormulaTree^ Steps;
        };
    }
}
