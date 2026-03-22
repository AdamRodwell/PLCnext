==============================================================================
Utils  (src/libs/Utils)
==============================================================================

A header-only / lightly-compiled C++ utility library for PLCnext programs.
All classes live in the  Utils  namespace.  Include headers from "Utils/...".

  #include "Utils/Timer.hpp"       // TON, TOF, TP timers
  #include "Utils/EdgeTrigger.hpp" // R_TRIG / F_TRIG edge detection
  #include "Utils/Alert.hpp"       // Base class for structured error reporting

------------------------------------------------------------------------------
Timer.hpp  —  IEC 61131-3 timers (TON / TOF / TP)
------------------------------------------------------------------------------

Call update(bool in) every PLC cycle.  Read Q() for the output and ET() for
elapsed time.  All preset times use std::chrono::milliseconds.

  // TON — turns ON after input has been true for >= PT
  Utils::TON ton{std::chrono::milliseconds(500)};
  ton.update(inputSignal);
  if (ton.Q()) { /* input has been true for 500 ms */ }

  // TOF — stays ON for PT after input goes false
  Utils::TOF tof{std::chrono::milliseconds(1000)};
  tof.update(inputSignal);
  if (tof.Q()) { /* output still active */ }

  // TP — single pulse of exactly PT on rising edge (non-retriggerable)
  Utils::TP tp{std::chrono::milliseconds(200)};
  tp.update(inputSignal);
  if (tp.Q()) { /* pulse active */ }

------------------------------------------------------------------------------
EdgeTrigger.hpp  —  rising / falling / both-edge detection
------------------------------------------------------------------------------

Three modes:
  Standard   — Q() true for exactly one Execute() cycle after the edge.
  Hold       — Q() true until clear() is called.
  Timed hold — Q() true for N milliseconds after the edge.

  // Tracked: EdgeTrigger watches the bool variable automatically
  bool mySignal = false;
  Utils::EdgeTrigger rTrig{mySignal, Utils::TriggerEdge::RISING};
  // ... in Execute():
  rTrig.update();
  if (rTrig.Q()) { /* rising edge detected this cycle */ }

  // Untracked: pass the value manually each cycle
  Utils::EdgeTrigger fTrig{Utils::TriggerEdge::FALLING};
  fTrig.update(someCondition);
  if (fTrig.Q()) { /* falling edge */ }

  // Timed hold — Q stays true for 250 ms after the edge
  Utils::EdgeTrigger held{mySignal, Utils::TriggerEdge::RISING, (int64_t)250};

------------------------------------------------------------------------------
Alert.hpp  —  structured error / warning reporting
------------------------------------------------------------------------------

Inherit from Utils::Alert and implement severity(), activeCode(), and clear().
hasError() / hasWarning() / status() are provided automatically by the base.

Pre-defined error codes are in Utils::ErrorCodes (NONE, GENERAL, TIMEOUT,
SENSOR_FAILURE, COMM_FAILURE, UNEXPECTED_STATE, SUBSYSTEM_FAULT).
Add application-specific codes starting at 0x0100 in your derived struct.

  struct MyErrors : public Utils::Alert
  {
      Utils::ErrorSeverity severity()   const override { return sev_; }
      Utils::ErrorCode     activeCode() const override { return code_; }
      void                 clear()            override { sev_ = Utils::ErrorSeverity::NONE;
                                                         code_ = Utils::ErrorCodes::NONE; }

      Utils::ErrorSeverity sev_  = Utils::ErrorSeverity::NONE;
      Utils::ErrorCode     code_ = Utils::ErrorCodes::NONE;
  };

  MyErrors err;
  err.sev_  = Utils::ErrorSeverity::ERROR;
  err.code_ = Utils::ErrorCodes::SENSOR_FAILURE;
  if (err.hasError()) { /* handle it */ }
