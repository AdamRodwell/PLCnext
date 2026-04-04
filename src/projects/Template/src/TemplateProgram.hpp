#pragma once
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Chrono/SystemTick.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/Arp.h"
#include "TemplateComponent.hpp"
#include "Utils/Alert.hpp"
#include "Utils/EdgeTrigger.hpp"
#include "Utils/Timer.hpp"
#include <boost/optional.hpp>

// TODO: add sub-system includes

namespace Template
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::System::Commons::Chrono;
using namespace Arp::Plc::Commons::Esm;
using namespace Utils;

// ============================================================================
// Error class — defined outside the program so it can be used as a port
// type and read by other programs.
//
// Add one public Arp::boolean per fault condition.
//   warning* prefix — non-critical (WARNING severity)
//   error*   prefix — critical     (ERROR severity)
// ============================================================================
class TemplateProgramError : public Alert
{
  public:
    // --- Warnings ---
    Arp::boolean warningExampleTimeout      = false; // TODO: rename / add real warnings
    Arp::boolean warningExampleSensorFailed = false;

    // --- Errors ---
    Arp::boolean errorExampleUnexpectedMode = false; // TODO: rename / add real errors

    inline ErrorSeverity severity() const override
    {
        if (errorExampleUnexpectedMode)
            return ErrorSeverity::ERROR;
        if (warningExampleTimeout || warningExampleSensorFailed)
            return ErrorSeverity::WARNING;
        return ErrorSeverity::NONE;
    }

    inline ErrorCode activeCode() const override
    {
        if (errorExampleUnexpectedMode)
            return ErrorCodes::UNEXPECTED_STATE;
        if (warningExampleTimeout)
            return ErrorCodes::TIMEOUT;
        if (warningExampleSensorFailed)
            return ErrorCodes::SENSOR_FAILURE;
        return ErrorCodes::NONE;
    }

    inline void clear() override
    {
        warningExampleTimeout      = false;
        warningExampleSensorFailed = false;
        errorExampleUnexpectedMode = false;
        // TODO: clear all flags
    }

    inline void ackWarnings()
    {
        warningExampleTimeout      = false;
        warningExampleSensorFailed = false;
        // TODO: clear all warning-only flags
    }
};

// ============================================================================
//#program
//#component(Template::TemplateComponent)
class TemplateProgram : public ProgramBase, private Loggable<TemplateProgram>
{
  public:
    enum class TemplateProgramMode : Arp::uint8
    {
        DISABLED     = 0x00,
        INITIALISING = 0x01,
        IDLE         = 0x02,
        // TODO: add operation-specific states
        MANUAL_MODE = 0xFE,
        ERROR       = 0xFF
    };

    struct TemplateProgramConfig
    {
        // TODO: replace with real config fields
        Arp::uint32 exampleTimeoutMs     = 5000;
        Arp::float32 examplePositionMm   = 0.0f;
        Arp::boolean exampleIgnoreSensor = false;
    };

    struct TemplateProgramMan
    {
        // TODO: add manual control fields
        Arp::boolean activateOutput = false;
        Arp::float32 manualSetpoint = 0.0f;
    };

    struct TemplateProgramCmd
    {
        Arp::boolean disable         = false;
        Arp::boolean initialise      = false;
        Arp::boolean startCycle      = false; // TODO: rename / add operation commands
        Arp::boolean enterManualMode = false;

        TemplateProgramMan manual;
    };

    struct TemplateProgramData
    {
        Arp::boolean isInitialisationDone = false;
        Arp::boolean isCycleDone          = false; // TODO: replace with real status flags
        Arp::uint32 cycleCount            = 0;

        TemplateProgramMode currentState = TemplateProgramMode::DISABLED;
        TemplateProgramError error;
    };

  public: // construction/destruction
    TemplateProgram(Template::TemplateComponent &templateComponentArg, const String &name);
#if ARP_ABI_VERSION_MAJOR < 2
    TemplateProgram(const TemplateProgram &arg) = delete;
    virtual ~TemplateProgram()                  = default;
#endif

  public: // operators
#if ARP_ABI_VERSION_MAJOR < 2
    TemplateProgram &operator=(const TemplateProgram &arg) = delete;
#endif

  public: // operations
    void Execute() override;

  public: /* ---- Ports ---------------------------------------------------------
               //#port
               //#attributes(Input|Output|Opc|Retain)
               //#name(<HMI tag name>)
             -------------------------------------------------------------------*/
    //#port
    //#attributes(Input|Opc|Retain)
    //#name(Config)
    TemplateProgramConfig config_;

    //#port
    //#attributes(Output|Opc)
    //#name(Data)
    TemplateProgramData data_;

    // TODO: add output command ports for sub-systems

    //#port
    //#attributes(Output|Opc)
    //#name(SystemTemplateError)
    TemplateProgramError systemTemplateError;

    //#port
    //#attributes(Input|Opc)
    //#name(Command)
    TemplateProgramCmd cmd_;

    // TODO: add input data ports from sub-systems

    //#port
    //#attributes(Input|Opc)
    //#name(ExampleSensor)
    Arp::boolean exampleSensor_ = false; // TODO: rename / add real sensor ports

  private: // fields
    Template::TemplateComponent &templateComponent;

    // Edge triggers — call .update() at top of Execute(), read .check() in state cases.
    EdgeTrigger initialiseEdge_{command_.initialise, TriggerEdge::RISING};
    EdgeTrigger startCycleEdge_{command_.startCycle, TriggerEdge::RISING, true};
    // TODO: add EdgeTrigger fields for all command/sensor signals that gate transitions

    // IEC timers — call .update(condition) before the switch; read .Q() inside states.
    TON exampleDelayTimer_{std::chrono::milliseconds(0)}; // TODO: rename, set PT from config

    Arp::boolean agentInitialising_     = false;
    Arp::boolean agentInitialisingDone_ = false;

  private:
};

std::string
toString(const TemplateProgramError &errorInstance);

///////////////////////////////////////////////////////////////////////////////
// inline methods of class TemplateProgram
inline TemplateProgram::TemplateProgram(Template::TemplateComponent &templateComponentArg,
                                        const String &name)
    : ProgramBase(name), templateComponent(templateComponentArg)
{
}

} // end of namespace Template
