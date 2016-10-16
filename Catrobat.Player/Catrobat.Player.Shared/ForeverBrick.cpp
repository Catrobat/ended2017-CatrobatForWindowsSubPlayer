#include "pch.h"
#include "ForeverBrick.h"
#include "Interpreter.h"

using namespace std;
using namespace ProjectStructure;


ForeverBrick::ForeverBrick(Catrobat_Player::NativeComponent::IForeverBrick^ brick, Script* parent) :
    ContainerBrick(TypeOfBrick::ContainerBrick, parent), m_stop(false)
{
}

ForeverBrick::~ForeverBrick()
{
}

void ForeverBrick::Execute()
{
    while (!m_stop)
    {
        for each (auto &brick in m_brickList)
        {
            brick->Execute();
            Concurrency::wait(20); // 50 Hz
        }
    }
    m_cv.notify_one();
}

void ForeverBrick::Stop()
{
    m_stop = true;
    std::unique_lock<std::mutex> lk(m_mutex);
    m_cv.wait(lk);
}