#include "Utils/EdgeTrigger.hpp"
#include <cstdio>

namespace Utils
{

EdgeTrigger::EdgeTrigger(bool &signal, TriggerEdge edge)
    : signal_(signal), edge_(edge), isTracked_(true)
{
}

EdgeTrigger::EdgeTrigger(bool &signal, TriggerEdge edge, bool hold)
    : signal_(signal), edge_(edge), isTracked_(true)
{
    (void)hold;
}

EdgeTrigger::EdgeTrigger(bool &signal, TriggerEdge edge, int64_t holdMillis)
    : signal_(signal), edge_(edge), isTracked_(true), holdMs_(holdMillis)
{
}

EdgeTrigger::EdgeTrigger(TriggerEdge edge)
    : signal_(current_), edge_(edge), isTracked_(false)
{
}

void
EdgeTrigger::update()
{
    if (!isTracked_)
    {
        fprintf(stderr, "EdgeTrigger::update() called on an untracked instance — use update(bool)\n");
        return;
    }
    current_ = signal_;
    detect();
}

void
EdgeTrigger::update(bool clk)
{
    current_ = clk;
    detect();
}

void
EdgeTrigger::clear()
{
    Q_         = false;
    held_      = false;
    holdTimer_ = boost::none;
}

void
EdgeTrigger::setHoldMillis(int64_t ms)
{
    holdMs_    = ms;
    holdTimer_ = boost::none;
}

void
EdgeTrigger::detect()
{
    const bool rising  =  current_ && !prev_;
    const bool falling = !current_ &&  prev_;

    const bool fired = (edge_ == TriggerEdge::RISING  && rising)
                    || (edge_ == TriggerEdge::FALLING  && falling)
                    || (edge_ == TriggerEdge::BOTH     && (rising || falling));

    if (fired)
    {
        Q_    = true;
        held_ = true;
        if (holdMs_ != kNoHold)
            holdTimer_ = Timer();
    }
    else if (!held_)
    {
        Q_ = false;
    }
    else if (holdTimer_ && holdTimer_->elapsedMilliseconds() >= holdMs_)
    {
        Q_         = false;
        held_      = false;
        holdTimer_ = boost::none;
    }

    prev_ = current_;
}

} // namespace Utils
