Valves — PLCnext header-only valve library
==========================================

Provides reusable valve control classes for the ARP (Automation Runtime Platform)
framework targeting the AXCF2152 controller.

Depends on: Utils (Alert.hpp, Timer.hpp)

Classes
-------

ValveBase (include/Valves/ValveBase.hpp)
  Abstract base class for all valve types.
  - Defines ValveState enum: CLOSED, OPENING, OPEN, CLOSING, FAULT
  - Defines ValveAlert: concrete Alert implementation for valve faults
  - Pure-virtual interface: update(), cmdOpen(), cmdClose(), reset()
  - Accessors: state(), alert(), isOpen(), isClosed(), hasFault()

MotorValve (include/Valves/MotorValve.hpp)
  Motorized (actuated) valve with separate open/close outputs and
  end-position feedback. Uses TON timer from Utils/Timer.hpp to
  detect travel timeout.
  - Constructor: MotorValve(travelTimeoutMs)
  - update(cmdOpen, cmdClose, fbOpen, fbClose): call each scan cycle
  - outOpen() / outClose(): drive the actuator
  - Raises ErrorCodes::TIMEOUT on travel timeout
  - Raises ErrorCodes::UNEXPECTED_STATE on simultaneous feedback conflict

SolenoidValve (include/Valves/SolenoidValve.hpp)
  Two-position, spring-return solenoid valve. Single coil output;
  optional feedback input. Uses TON timer to detect coil response
  timeout.
  - Constructor: SolenoidValve(responseTimeoutMs)
  - update(cmd, fb): call each scan cycle (fb optional — pass false if
    no feedback sensor is wired)
  - out(): coil drive signal
  - Raises ErrorCodes::TIMEOUT if feedback does not follow command
    within the configured timeout (when fb wired)

Build
-----
  cd src/libs/Valves
  export BUILD_TYPE=Release
  plcncli build --verbose
  plcncli deploy
