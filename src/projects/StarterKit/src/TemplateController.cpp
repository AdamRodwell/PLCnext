#include "TemplateController.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/ByteConverter.hpp"

namespace StarterKit
{

TemplateController::TemplateController(StarterKit::StarterKitComponent &StarterKitComponentArg,
                                       const String &name)
    : ProgramBase(name), StarterKitComponent(StarterKitComponentArg)
{
}

namespace
{
// TODO: add file-local pure utility helpers here
} // namespace

void
TemplateController::CheckSubSystemErrors()
{
    // TODO: mirror sub-system error/warning flags into data_.error, e.g.:
    // data_.error.hasErrorSubSystem   = dataSubSystem_.error.hasError();
    // data_.error.hasWarningSubSystem = dataSubSystem_.error.hasWarning();
    (void)this;
}

// TODO: implement additional private methods, e.g.:
// void TemplateController::SafetyCheck() { ... }

void
TemplateController::Execute()
{
    try
    {
        // 1. Update edge detectors
        initialiseEdge_.update();
        startCycleEdge_.update();
        // TODO: call .update() on all edge detectors

        // 2. Aggregate sub-system errors
        CheckSubSystemErrors();
        systemTemplateError = data_.error;

        // 3. Global disable / error guard
        if (command_.disable || (data_.error.hasError() && !command_.initialise))
        {
            data_.currentState = TemplateControllerState::DISABLED;
            // TODO: drive sub-system commands to safe defaults
        }

        // 4. State machine
        switch (data_.currentState)
        {
        case TemplateControllerState::DISABLED:
            data_.isInitialisationDone = false;
            data_.isCycleDone          = false;
            data_.cycleCount           = 0;

            exampleDelayTimer_.update(false);
            agentInitialising_     = false;
            agentInitialisingDone_ = false;

            // TODO: drive all sub-system command ports to their safe/off state

            if (command_.enterManualMode)
            {
                data_.currentState = TemplateControllerState::MANUAL_MODE;
                log.Info("{0}: Entering MANUAL_MODE from DISABLED", GetFullName());
            }
            else if (initialiseEdge_.check())
            {
                data_.currentState = TemplateControllerState::INITIALISING;
                log.Info("{0}: Entering INITIALISING", GetFullName());
            }
            break;

        case TemplateControllerState::INITIALISING:
            if (!agentInitialising_)
            {
                // TODO: send reset/initialise commands to sub-systems
                agentInitialising_ = true;
                log.Debug("{0}: Sending init commands to sub-systems", GetFullName());
            }
            else if (!agentInitialisingDone_)
            {
                data_.error.clear();
                agentInitialisingDone_ = true;
                log.Debug("{0}: Errors cleared, waiting for sub-systems", GetFullName());
            }
            else
            {
                // TODO: replace with real sub-system ready check
                bool subSystemReady = true;

                if (subSystemReady)
                {
                    data_.isInitialisationDone = true;
                    data_.currentState         = TemplateControllerState::IDLE;
                    log.Info("{0}: Initialisation complete, entering IDLE", GetFullName());
                }
                else
                {
                    log.Trace("{0}: Waiting for sub-system ready...", GetFullName());
                }
            }
            break;

        case TemplateControllerState::IDLE:
            data_.isCycleDone = false;

            if (command_.enterManualMode)
            {
                data_.currentState = TemplateControllerState::MANUAL_MODE;
                log.Info("{0}: Entering MANUAL_MODE from IDLE", GetFullName());
            }
            else if (startCycleEdge_.check())
            {
                data_.cycleCount++;
                data_.error.clearWarnings();
                startCycleEdge_.clear();
                // TODO: transition to first operation state
                log.Info("{0}: Cycle {1} started", GetFullName(), data_.cycleCount);
            }
            break;

            // TODO: add operation-specific states, e.g.:
            //
            // case TemplateControllerState::FIRST_OP_STATE:
            //     exampleDelayTimer_.setPT(std::chrono::milliseconds(config_.exampleTimeoutMs));
            //     exampleDelayTimer_.update(true);
            //     SafetyCheck();
            //     if (exampleDelayTimer_.Q())
            //     {
            //         data_.error.errorExampleUnexpectedState = true;
            //         exampleDelayTimer_.update(false);
            //         data_.currentState = TemplateControllerState::ERROR;
            //         break;
            //     }
            //     if (<done condition>)
            //     {
            //         exampleDelayTimer_.update(false);
            //         data_.currentState = TemplateControllerState::IDLE;
            //     }
            //     break;

        case TemplateControllerState::MANUAL_MODE:
            if (!command_.enterManualMode)
            {
                if (!data_.error.hasError())
                {
                    log.Info("{0}: Leaving MANUAL_MODE", GetFullName());
                    data_.currentState = TemplateControllerState::INITIALISING;
                }
                else
                {
                    log.Warning("{0}: Leaving MANUAL_MODE with errors — entering ERROR",
                                GetFullName());
                    data_.currentState = TemplateControllerState::ERROR;
                    break;
                }
            }
            // TODO: drive outputs from command_.manual fields
            break;

        case TemplateControllerState::ERROR:
            // TODO: drive all outputs to safe state
            data_.currentState = TemplateControllerState::DISABLED;
            log.Error("{0}: Entered ERROR state — {1}", GetFullName(), toString(data_.error));
            break;

        default:
            log.Warning("{0}: Unknown state {1} — forcing DISABLED", GetFullName(),
                        static_cast<Arp::uint8>(data_.currentState));
            data_.currentState = TemplateControllerState::DISABLED;
            break;
        }

    } // try
    catch (const std::exception &e)
    {
        log.Error("{0}: Exception in Execute(): {1}", GetFullName(), e.what());
        data_.error.errorExampleUnexpectedState = true;
        data_.currentState                      = TemplateControllerState::ERROR;
    }
    catch (...)
    {
        log.Error("{0}: Unknown exception in Execute()", GetFullName());
        data_.error.errorExampleUnexpectedState = true;
        data_.currentState                      = TemplateControllerState::ERROR;
    }
}

// Returns a human-readable summary of all active error/warning flags.
std::string
toString(const TemplateControllerError &e)
{
    std::string msg;

    if (e.warningExampleTimeout)
        msg += "WARNING: Operation timed out\n";
    if (e.warningExampleSensorFailed)
        msg += "WARNING: Sensor did not respond\n";
    if (e.hasWarningSubSystem)
        msg += "WARNING: Sub-system warning active\n";
    if (e.errorExampleUnexpectedState)
        msg += "ERROR: Unexpected state\n";
    if (e.hasErrorSubSystem)
        msg += "ERROR: Sub-system fault\n";
    // TODO: add a line for every error/warning flag

    if (msg.empty())
        msg = "No active errors";
    return msg;
}

} // namespace StarterKit
