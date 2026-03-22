#pragma once
// IEC 61131-3 R_TRIG / F_TRIG combined into one configurable class.
//
// Modes:
//   Standard  — Q true for exactly one Execute() cycle after the edge fires.
//   Hold      — Q true until clear() is called (pass hold=true).
//   Timed hold — Q true for N milliseconds (pass holdMillis > 0).

#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/Arp.h"
#include "Utils/Timer.hpp"
#include <boost/optional.hpp>

namespace Utils
{

using namespace Arp::System::Commons::Diagnostics::Logging;

enum class TriggerEdge : Arp::uint8
{
    RISING,  // R_TRIG: 0→1
    FALLING, // F_TRIG: 1→0
    BOTH
};

class EdgeTrigger
{
  public:
    // Tracked — signal read automatically by update().
    EdgeTrigger(bool &signal, TriggerEdge edge);
    EdgeTrigger(bool &signal, TriggerEdge edge, bool hold);
    EdgeTrigger(bool &signal, TriggerEdge edge, int64_t holdMillis);

    // Untracked — caller passes current value to update(bool).
    explicit EdgeTrigger(TriggerEdge edge);

    ~EdgeTrigger() = default;

    void update();
    void update(bool clk);

    bool Q()     const { return Q_; }
    bool check() const { return Q_; }
    void clear();

    void setHoldMillis(int64_t ms);

    static constexpr int64_t kNoHold = -1;

  private:
    bool &signal_;
    bool  current_   = false;
    bool  prev_      = false;
    bool  Q_         = false;
    bool  held_      = false;

    TriggerEdge edge_;
    bool        isTracked_;

    boost::optional<Timer> holdTimer_ = boost::none;
    int64_t                holdMs_    = kNoHold;

    void detect();
};

} // namespace Utils
