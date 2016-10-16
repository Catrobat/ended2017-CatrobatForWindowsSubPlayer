#pragma once

#include "ContainerBrick.h"
#include "Object.h"
#include "IForeverBrick.h"

#include <condition_variable>
#include <list>

namespace ProjectStructure
{
	class ForeverBrick :
		public ContainerBrick
	{
	public:
		ForeverBrick(Catrobat_Player::NativeComponent::IForeverBrick^ brick, Script* parent);
		~ForeverBrick();

		void Execute();
        void Stop();
	private:
        bool m_stop;
        std::condition_variable m_cv;
        std::mutex m_mutex;
    };
}
