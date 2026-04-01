#pragma once
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/Arp.h"
#include "StarterKitComponent.hpp"
#include "Utils/EdgeTrigger.hpp"
#include "Utils/Scale.hpp"
#include "Utils/Timer.hpp"

namespace StarterKit
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(StarterKit::StarterKitComponent)
class StarterKitProgram : public ProgramBase, private Loggable<StarterKitProgram>
{
  public: // typedefs
    struct StarterKitCommand
    {
        Arp::boolean readAnalog1 = false;

        Arp::boolean setOutput = false;
    };

    struct analogConfig
    {
        Arp::uint32 minRange = 0;
        Arp::uint32 maxRange = 0;
    };

    struct StarterKitConfig
    {
        Arp::boolean allowOutputs = false;
        Arp::uint32 minRange      = 0;
        analogConfig analogInOne;
    };

    struct StarterKitData
    {
        Arp::boolean areOutPutActive = false;
    };

  public: // construction/destruction
    StarterKitProgram(StarterKit::StarterKitComponent &starterKitComponentArg, const String &name);
    StarterKitProgram(const StarterKitProgram &arg) = delete;
    virtual ~StarterKitProgram()                    = default;

  public: // operators
    StarterKitProgram &operator=(const StarterKitProgram &arg) = delete;

  public: // properties
  public: // operations
    void Execute() override;

  public: /* Ports
             =====
             Ports are defined in the following way:
             //#port
             //#attributes(Input|Retain)
             //#name(NameOfPort)
             boolean portField;

             The attributes comment define the port attributes and is optional.
             The name comment defines the name of the port and is optional. Default is the name of
             the field.
          */
          // Inputs

    //#port
    //#attributes(Input|Opc)
    //#name(Command)
    StarterKitCommand command_;

    //#port
    //#attributes(Input|Opc)
    //#name(Config)
    StarterKitConfig config_;

    //#port
    //#attributes(Output|Opc)
    //#name(Data)
    StarterKitData data_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN01)
    Arp::boolean digitalIn1_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN02)
    Arp::boolean dIN02_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN03)
    Arp::boolean dIN03_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN04)
    Arp::boolean dIN04_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN05)
    Arp::boolean dIN05_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN06)
    Arp::boolean dIN06_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN07)
    Arp::boolean dIN07_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN08)
    Arp::boolean dIN08_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN09)
    Arp::boolean dIN09_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN10)
    Arp::boolean dIN10_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN11)
    Arp::boolean dIN11_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN12)
    Arp::boolean dIN12_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN13)
    Arp::boolean dIN13_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN14)
    Arp::boolean dIN14_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN15)
    Arp::boolean dIN15_;

    //#port
    //#attributes(Input|Opc)
    //#name(DIN16)
    Arp::boolean dIN16_;

    //#port
    //#attributes(Input|Opc)
    //#name(AIN1)
    Arp::uint32 aiN1_;

    //#port
    //#attributes(Input|Opc)
    //#name(AIN2)
    Arp::uint32 aiN2_;

    //#port
    //#attributes(Input|Opc)
    //#name(AIN3)
    Arp::uint32 aiN3_;

    //#port
    //#attributes(Input|Opc)
    //#name(AIN4)
    Arp::uint32 aiN4_;

    // Outputs

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT01)
    Arp::boolean dOUT01_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT02)
    Arp::boolean dOUT02_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT03)
    Arp::boolean dOUT03_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT04)
    Arp::boolean dOUT04_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT05)
    Arp::boolean dOUT05_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT06)
    Arp::boolean dOUT06_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT07)
    Arp::boolean dOUT07_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT08)
    Arp::boolean dOUT08_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT09)
    Arp::boolean dOUT09_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT10)
    Arp::boolean dOUT10_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT11)
    Arp::boolean dOUT11_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT12)
    Arp::boolean dOUT12_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT13)
    Arp::boolean dOUT13_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT14)
    Arp::boolean dOUT14_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT15)
    Arp::boolean dOUT15_;

    //#port
    //#attributes(Output|Opc)
    //#name(DOUT16)
    Arp::boolean dOUT16_;

  private: // fields
    StarterKit::StarterKitComponent &starterKitComponent;

    // Utils: detect rising edge of readAnalog1 command so we log once per activation
    Utils::EdgeTrigger readAnalog1Trig_{Utils::TriggerEdge::RISING};

    // Utils: 500 ms on-delay before fan outputs are allowed to activate
    Utils::TON outputOnDelay_{std::chrono::milliseconds(500)};
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline StarterKitProgram::StarterKitProgram(StarterKit::StarterKitComponent &starterKitComponentArg,
                                            const String &name)
    : ProgramBase(name), starterKitComponent(starterKitComponentArg)
{
}

} // end of namespace StarterKit
