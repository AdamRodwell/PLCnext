#pragma once
// TON — on-delay, TOF — off-delay, TP — pulse  (IEC 61131-3)
// Interface: update(bool in), Q(), ET(), setPT()

#include "Arp/System/Commons/Chrono/SystemTick.hpp"
#include <boost/optional.hpp>
#include <chrono>
#include <cmath>

namespace Utils
{

using namespace Arp::System::Commons::Chrono;

// Internal elapsed-time helper used by TON / TOF / TP / EdgeTrigger.
class Timer
{
  public:
    Timer() : startUs_(SystemTick::GetMicroTick().count()) {}

    inline void    restart()             { startUs_ = SystemTick::GetMicroTick().count(); }
    inline int64_t elapsedMicroseconds() const
    {
        return static_cast<int64_t>(
            std::fabs(static_cast<double>(SystemTick::GetMicroTick().count() - startUs_)));
    }
    inline int64_t elapsedMilliseconds() const { return elapsedMicroseconds() / 1000; }

  private:
    int64_t startUs_ = 0;
};

// Q true after IN has been continuously true for >= PT.
class TON
{
  public:
    explicit TON(std::chrono::milliseconds pt) : ptMs_(pt.count()) {}

    inline void update(bool in)
    {
        if (in)
        {
            if (!timer_)
                timer_ = Timer();

            const int64_t e = timer_->elapsedMilliseconds();
            Q_  = (e >= ptMs_);
            ET_ = std::chrono::milliseconds(e < ptMs_ ? e : ptMs_);
        }
        else
        {
            timer_ = boost::none;
            Q_     = false;
            ET_    = std::chrono::milliseconds(0);
        }
    }

    inline bool                       Q()  const { return Q_; }
    inline std::chrono::milliseconds  ET() const { return ET_; }
    inline void setPT(std::chrono::milliseconds pt) { ptMs_ = pt.count(); }

  private:
    int64_t                   ptMs_;
    boost::optional<Timer>    timer_;
    bool                      Q_  = false;
    std::chrono::milliseconds ET_ {0};
};

// Q true while IN true; stays true for PT after IN falls.
class TOF
{
  public:
    explicit TOF(std::chrono::milliseconds pt) : ptMs_(pt.count()) {}

    inline void update(bool in)
    {
        if (in)
        {
            Q_     = true;
            timer_ = boost::none;
            ET_    = std::chrono::milliseconds(0);
        }
        else if (Q_)
        {
            if (!timer_)
                timer_ = Timer();

            const int64_t e = timer_->elapsedMilliseconds();
            ET_ = std::chrono::milliseconds(e < ptMs_ ? e : ptMs_);

            if (e >= ptMs_)
            {
                Q_     = false;
                timer_ = boost::none;
            }
        }
    }

    inline bool                       Q()  const { return Q_; }
    inline std::chrono::milliseconds  ET() const { return ET_; }
    inline void setPT(std::chrono::milliseconds pt) { ptMs_ = pt.count(); }

  private:
    int64_t                   ptMs_;
    boost::optional<Timer>    timer_;
    bool                      Q_  = false;
    std::chrono::milliseconds ET_ {0};
};

// Q true for exactly PT on rising edge of IN; non-retriggerable.
class TP
{
  public:
    explicit TP(std::chrono::milliseconds pt) : ptMs_(pt.count()) {}

    inline void update(bool in)
    {
        const bool rising = in && !prev_;

        if (rising && !Q_)
        {
            Q_     = true;
            timer_ = Timer();
        }

        if (Q_)
        {
            const int64_t e = timer_->elapsedMilliseconds();
            ET_ = std::chrono::milliseconds(e < ptMs_ ? e : ptMs_);

            if (e >= ptMs_)
            {
                Q_     = false;
                timer_ = boost::none;
                ET_    = std::chrono::milliseconds(0);
            }
        }

        prev_ = in;
    }

    inline bool                       Q()  const { return Q_; }
    inline std::chrono::milliseconds  ET() const { return ET_; }
    inline void setPT(std::chrono::milliseconds pt) { ptMs_ = pt.count(); }

  private:
    int64_t                   ptMs_;
    boost::optional<Timer>    timer_;
    bool                      Q_    = false;
    bool                      prev_ = false;
    std::chrono::milliseconds ET_   {0};
};

} // namespace Utils
