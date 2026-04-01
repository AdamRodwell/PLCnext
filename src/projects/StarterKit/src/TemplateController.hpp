#pragma once
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/Arp.h"
#include "StarterKitComponent.hpp"
#include "Arp/System/Commons/Chrono/SystemTick.hpp"
#include "Utils/Alert.hpp"
#include "Utils/EdgeTrigger.hpp"
#include "Utils/Timer.hpp"
#include <boost/optional.hpp>

// TODO: add sub-system includes

namespace StarterKit
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::System::Commons::Chrono;
using namespace Arp::Plc::Commons::Esm;
using namespace Utils;

// ============================================================================
// Error class — defined outside the controller so it can be used as a port
// type and read by other programs.
//
// Add one public Arp::boolean per fault condition.
//   warning* prefix — non-critical (WARNING severity)
//   error*   prefix — critical     (ERROR severity)
// ============================================================================
class TemplateControllerError : public Alert
{
  public:
    // --- Warnings ---
    Arp::boolean warningExampleTimeout      = false; // TODO: rename / add real warnings
    Arp::boolean warningExampleSensorFailed = false;

    // --- Errors ---
    Arp::boolean errorExampleUnexpectedState = false; // TODO: rename / add real errors

    // --- Aggregated sub-system faults ---
    Arp::boolean hasErrorSubSystem   = false;
    Arp::boolean hasWarningSubSystem = false;

    inline ErrorSeverity severity() const override
    {
        if (errorExampleUnexpectedState || hasErrorSubSystem)
            return ErrorSeverity::ERROR;
        if (warningExampleTimeout || warningExampleSensorFailed || hasWarningSubSystem)
            return ErrorSeverity::WARNING;
        return ErrorSeverity::NONE;
    }

    inline ErrorCode activeCode() const override
    {
        if (errorExampleUnexpectedState)
            return ErrorCodes::UNEXPECTED_STATE;
        if (hasErrorSubSystem)
            return ErrorCodes::SUBSYSTEM_FAULT;
        if (warningExampleTimeout)
            return ErrorCodes::TIMEOUT;
        if (warningExampleSensorFailed)
            return ErrorCodes::SENSOR_FAILURE;
        if (hasWarningSubSystem)
            return ErrorCodes::SUBSYSTEM_FAULT;
        return ErrorCodes::NONE;
    }

    inline void clear() override
    {
        warningExampleTimeout       = false;
        warningExampleSensorFailed  = false;
        errorExampleUnexpectedState = false;
        hasErrorSubSystem           = false;
        hasWarningSubSystem         = false;
        // TODO: clear all flags
    }

    inline void clearWarnings()
    {
        warningExampleTimeout      = false;
        warningExampleSensorFailed = false;
        hasWarningSubSystem        = false;
        // TODO: clear all warning-only flags
    }
};

// ============================================================================
//#program
//#component(StarterKit::StarterKitComponent)
class TemplateController : public ProgramBase, private Loggable<TemplateController>
{
  public:
    enum class TemplateControllerState : Arp::uint8
    {
        DISABLED     = 0x00,
        INITIALISING = 0x01,
        IDLE         = 0x02,
        // TODO: add operation-specific states
        MANUAL_MODE = 0xFE,
        ERROR       = 0xFF
    };

    struct TemplateConfig
    {
        // TODO: replace with real config fields
        Arp::uint32 exampleTimeoutMs     = 5000;
        Arp::float32 examplePositionMm   = 0.0f;
        Arp::boolean exampleIgnoreSensor = false;
    };

    struct TemplateManualCommand
    {
        // TODO: add manual control fields
        Arp::boolean activateOutput = false;
        Arp::float32 manualSetpoint = 0.0f;
    };

    struct TemplateCommand
    {
        Arp::boolean disable         = false;
        Arp::boolean initialise      = false;
        Arp::boolean startCycle      = false; // TODO: rename / add operation commands
        Arp::boolean enterManualMode = false;

        TemplateManualCommand manual;
    };

    struct TemplateData
    {
        Arp::boolean isInitialisationDone = false;
        Arp::boolean isCycleDone          = false; // TODO: replace with real status flags
        Arp::uint32 cycleCount            = 0;

        TemplateControllerState currentState = TemplateControllerState::DISABLED;
        TemplateControllerError error;
    };

  public:
    TemplateController(StarterKit::StarterKitComponent &StarterKitComponentArg, const String &name);
    TemplateController(const TemplateController &arg) = delete;
    virtual ~TemplateController()                     = default;

    TemplateController &operator=(const TemplateController &arg) = delete;

    void Execute() override;

  public: /* ---- Ports -------------------------------------------------------
               //#port
               //#attributes(Input|Output|Opc|Retain)
               //#name(<HMI tag name>)
             ----------------------------------------------------------------- */
    //#port
    //#attributes(Input|Opc|Retain)
    //#name(Config)
    TemplateConfig config_;

    //#port
    //#attributes(Output|Opc)
    //#name(Data)
    TemplateData data_;

    // TODO: add output command ports for sub-systems

    //#port
    //#attributes(Output|Opc)
    //#name(SystemTemplateError)
    TemplateControllerError systemTemplateError;

    //#port
    //#attributes(Input|Opc)
    //#name(Command)
    TemplateCommand command_;

    // TODO: add input data ports from sub-systems

    //#port
    //#attributes(Input|Opc)
    //#name(ExampleSensor)
    Arp::boolean exampleSensor_ = false; // TODO: rename / add real sensor ports

  private:
    StarterKit::StarterKitComponent &StarterKitComponent;

    // Edge triggers — call .update() at top of Execute(), read .Q() in state cases.
    EdgeTrigger initialiseEdge_{command_.initialise, TriggerEdge::RISING};
    EdgeTrigger startCycleEdge_{command_.startCycle, TriggerEdge::RISING, true};
    // TODO: add EdgeTrigger fields for all command/sensor signals that gate transitions

    // IEC timers — call .update(condition) before the switch; read .Q() inside states.
    TON exampleDelayTimer_{std::chrono::milliseconds(0)}; // TODO: rename, set PT from config

    Arp::boolean agentInitialising_     = false;
    Arp::boolean agentInitialisingDone_ = false;

  private:
    void CheckSubSystemErrors();
    // TODO: add private helper declarations
};

std::string
toString(const TemplateControllerError &errorInstance);

} // namespace StarterKit
