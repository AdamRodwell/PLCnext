#pragma once
#include "Arp/System/Core/Arp.h"
#include "Utils/Alert.hpp"
#include "Utils/Timer.hpp"
#include <chrono>

namespace Valves
{

using namespace Arp;

// Operating state of any valve.
enum class ValveState : Arp::uint8
{
    CLOSED  = 0,
    OPENING = 1,
    OPEN    = 2,
    CLOSING = 3,
    FAULT   = 4,
};

// Valve-specific error codes (0x0100+).
namespace ErrorCodes
{
using Utils::ErrorCode;
constexpr ErrorCode NONE          = Utils::ErrorCodes::NONE;
constexpr ErrorCode TIMEOUT_OPEN  = 0x0100; // did not reach open  in time
constexpr ErrorCode TIMEOUT_CLOSE = 0x0101; // did not reach closed in time
} // namespace ErrorCodes

// Concrete Alert implementation shared by all valve types.
// Application-specific error codes start at 0x0100.
class ValveAlert : public Utils::Alert
{
  public:
    void raise(Utils::ErrorCode code, Utils::ErrorSeverity sev)
    {
        if (sev > severity_)
        {
            code_     = code;
            severity_ = sev;
        }
    }

    void clear() override
    {
        code_     = Utils::ErrorCodes::NONE;
        severity_ = Utils::ErrorSeverity::NONE;
    }

    Utils::ErrorSeverity severity() const override { return severity_; }
    Utils::ErrorCode activeCode() const override { return code_; }

  private:
    Utils::ErrorCode code_         = Utils::ErrorCodes::NONE;
    Utils::ErrorSeverity severity_ = Utils::ErrorSeverity::NONE;
};

// Abstract base class for all valve controllers.
//
// Owns transit timeout logic applicable to every valve type.
// hasFeedback controls timer behaviour:
//   false — timer expiry assumes position reached → transitions to OPEN/CLOSED
//   true  — timer expiry before feedback confirmation → FAULT
//
// Derived classes must implement:
//   update()   — called once per scan cycle; drives state machine
//   cmdOpen()  — request valve to open
//   cmdClose() — request valve to close
//   reset()    — clear faults and return to idle
//
// Derived classes report position via protected helpers:
//   tickTransit()    — call each cycle during OPENING/CLOSING; returns true if timer acted
//   confirmPosition()— call when feedback confirms valve has arrived
//   setFault()       — call to raise additional derived-class faults
class ValveBase
{
  public:
    // transitTimeout : time allowed to reach commanded position
    // hasFeedback    : true  = timeout triggers FAULT
    //                  false = timeout assumes position reached
    ValveBase(std::chrono::milliseconds transitTimeout, bool hasFeedback)
        : transitTimeout_(transitTimeout), hasFeedback_(hasFeedback), transitTimer_(transitTimeout)
    {
    }

    virtual void update()   = 0;
    virtual void cmdOpen()  = 0;
    virtual void cmdClose() = 0;
    virtual void reset()    = 0;

    ValveState state() const { return state_; }
    const ValveAlert &alert() const { return alert_; }
    bool isOpen() const { return state_ == ValveState::OPEN; }
    bool isClosed() const { return state_ == ValveState::CLOSED; }
    bool isOpening() const { return state_ == ValveState::OPENING; }
    bool isClosing() const { return state_ == ValveState::CLOSING; }
    bool hasFault() const { return state_ == ValveState::FAULT; }

    virtual ~ValveBase() = default;

  protected:
    // Call each cycle inside update() while in OPENING or CLOSING.
    // Returns true if the timer acted — derived class should return early.
    bool tickTransit()
    {
        const bool inTransit = state_ == ValveState::OPENING || state_ == ValveState::CLOSING;
        transitTimer_.update(inTransit);

        if (inTransit && transitTimer_.Q())
        {
            if (hasFeedback_)
            {
                setFault(state_ == ValveState::OPENING ? ErrorCodes::TIMEOUT_OPEN
                                                       : ErrorCodes::TIMEOUT_CLOSE);
            }
            else
            {
                state_ = (state_ == ValveState::OPENING) ? ValveState::OPEN : ValveState::CLOSED;
                transitTimer_.update(false);
            }
            return true;
        }
        return false;
    }

    // Call when feedback confirms the valve has reached its commanded position.
    void confirmPosition()
    {
        state_ = (state_ == ValveState::OPENING) ? ValveState::OPEN : ValveState::CLOSED;
        transitTimer_.update(false);
    }

    void setFault(Utils::ErrorCode code)
    {
        state_ = ValveState::FAULT;
        alert_.raise(code, Utils::ErrorSeverity::ERROR);
        transitTimer_.update(false);
    }

    void clearFault()
    {
        alert_.clear();
        state_ = ValveState::CLOSED;
    }

    std::chrono::milliseconds transitTimeout_;
    bool hasFeedback_;
    Utils::TON transitTimer_;
    ValveState state_ = ValveState::CLOSED;
    ValveAlert alert_;
};

} // namespace Valves