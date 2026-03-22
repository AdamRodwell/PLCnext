#pragma once
#include "Arp/System/Core/Arp.h"

namespace Utils
{

using namespace Arp;

// Priority order: NONE < WARNING < ERROR
enum class ErrorSeverity : Arp::uint8
{
    NONE    = 0,
    WARNING = 1,
    ERROR   = 2,
};

using ErrorCode = Arp::uint16;

namespace ErrorCodes
{
constexpr ErrorCode NONE             = 0x0000;
constexpr ErrorCode GENERAL          = 0x0001;
constexpr ErrorCode TIMEOUT          = 0x0002;
constexpr ErrorCode SENSOR_FAILURE   = 0x0003;
constexpr ErrorCode COMM_FAILURE     = 0x0004;
constexpr ErrorCode UNEXPECTED_STATE = 0x0005;
constexpr ErrorCode SUBSYSTEM_FAULT  = 0x0006;
// Application-specific: define 0x0100+ in your derived class
} // namespace ErrorCodes

// Base class for all controller error structs.
// Derived classes implement severity() and activeCode() only —
// hasError() / hasWarning() / status() are derived automatically.
class Alert
{
  public:
    virtual ErrorSeverity severity()   const = 0;
    virtual ErrorCode     activeCode() const = 0;
    virtual void          clear()            = 0;

    bool      hasError()   const { return severity() >= ErrorSeverity::ERROR;   }
    bool      hasWarning() const { return severity() >= ErrorSeverity::WARNING; }
    ErrorCode status()     const { return activeCode(); }

    virtual ~Alert() = default;
};

} // namespace Utils
