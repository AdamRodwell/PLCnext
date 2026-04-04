#include "TemplateProgram.hpp"
#include "Arp/System/Commons/Logging.h"
#if ARP_ABI_VERSION_MAJOR < 2
#include "Arp/System/Core/ByteConverter.hpp"
#else
#include "Arp/Base/Core/ByteConverter.hpp"
#endif

namespace Template
{

namespace
{
// TODO: add file-local pure utility helpers here
} // namespace

// TODO: implement additional private methods, e.g.:
// void TemplateProgram::SafetyCheck() { ... }

void
TemplateProgram::Execute()
{
    try
    {
        initialiseEdge_.update();
        startCycleEdge_.update();
        // TODO: call .update() on all edge detectors
        systemTemplateError = data_.error;

        if (command_.disable || (data_.error.hasError() && !command_.initialise))
        {
            data_.currentState = TemplateProgramMode::DISABLED;
        }

        switch (data_.currentState)
        {
        case TemplateProgramMode::DISABLED:
            data_.isInitialisationDone = false;
            data_.isCycleDone          = false;
            data_.cycleCount           = 0;

            exampleDelayTimer_.update(false);
            agentInitialising_     = false;
            agentInitialisingDone_ = false;

            if (command_.enterManualMode)
            {
                data_.currentState = TemplateProgramMode::MANUAL_MODE;
                log.Info("{0}: Entering MANUAL_MODE from DISABLED", GetFullName());
            }
            else if (initialiseEdge_.check())
            {
                data_.currentState = TemplateProgramMode::INITIALISING;
                log.Info("{0}: Entering INITIALISING", GetFullName());
            }
            break;

        case TemplateProgramMode::INITIALISING:
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
                    data_.currentState         = TemplateProgramMode::IDLE;
                    log.Info("{0}: Initialisation complete, entering IDLE", GetFullName());
                }
                else
                {
                    log.Trace("{0}: Waiting for sub-system ready...", GetFullName());
                }
            }
            break;

        case TemplateProgramMode::IDLE:
            data_.isCycleDone = false;

            if (command_.enterManualMode)
            {
                data_.currentState = TemplateProgramMode::MANUAL_MODE;
                log.Info("{0}: Entering MANUAL_MODE from IDLE", GetFullName());
            }
            else if (startCycleEdge_.check())
            {
                data_.cycleCount++;
                data_.error.ackWarnings();
                startCycleEdge_.clear();
                // TODO: transition to first operation state
                log.Info("{0}: Cycle {1} started", GetFullName(), data_.cycleCount);
            }
            break;

            // TODO: add operation-specific states, e.g.:
            //
            // case TemplateProgramMode::FIRST_OP_STATE:
            //     exampleDelayTimer_.setPT(std::chrono::milliseconds(config_.exampleTimeoutMs));
            //     exampleDelayTimer_.update(true);
            //     SafetyCheck();
            //     if (exampleDelayTimer_.Q())
            //     {
            //         data_.error.errorExampleUnexpectedMode = true;
            //         exampleDelayTimer_.update(false);
            //         data_.currentState = TemplateProgramMode::ERROR;
            //         break;
            //     }
            //     if (<done condition>)
            //     {
            //         exampleDelayTimer_.update(false);
            //         data_.currentState = TemplateProgramMode::IDLE;
            //     }
            //     break;

        case TemplateProgramMode::MANUAL_MODE:
            if (!command_.enterManualMode)
            {
                if (!data_.error.hasError())
                {
                    log.Info("{0}: Leaving MANUAL_MODE", GetFullName());
                    data_.currentState = TemplateProgramMode::INITIALISING;
                }
                else
                {
                    log.Warning("{0}: Leaving MANUAL_MODE with errors — entering ERROR",
                                GetFullName());
                    data_.currentState = TemplateProgramMode::ERROR;
                    break;
                }
            }
            // TODO: drive outputs from command_.manual fields
            break;

        case TemplateProgramMode::ERROR:
            // TODO: drive all outputs to safe state
            data_.currentState = TemplateProgramMode::DISABLED;
            log.Error("{0}: Entered ERROR state — {1}", GetFullName(), toString(data_.error));
            break;

        default:
            log.Warning("{0}: Unknown state {1} — forcing DISABLED", GetFullName(),
                        static_cast<Arp::uint8>(data_.currentState));
            data_.currentState = TemplateProgramMode::DISABLED;
            break;
        }

    } // try
    catch (const std::exception &e)
    {
        log.Error("{0}: Exception in Execute(): {1}", GetFullName(), e.what());
        data_.error.errorExampleUnexpectedMode = true;
        data_.currentState                     = TemplateProgramMode::ERROR;
    }
    catch (...)
    {
        log.Error("{0}: Unknown exception in Execute()", GetFullName());
        data_.error.errorExampleUnexpectedMode = true;
        data_.currentState                     = TemplateProgramMode::ERROR;
    }
}

// Returns a human-readable summary of all active error/warning flags.
std::string
toString(const TemplateProgramError &e)
{
    std::string msg;

    if (e.warningExampleTimeout)
        msg += "WARNING: Operation timed out\n";
    if (e.warningExampleSensorFailed)
        msg += "WARNING: Sensor did not respond\n";
    if (e.errorExampleUnexpectedMode)
        msg += "ERROR: Unexpected state\n";
    // TODO: add a line for every error/warning flag

    if (msg.empty())
        msg = "No active errors";
    return msg;
}

} // end of namespace Template
