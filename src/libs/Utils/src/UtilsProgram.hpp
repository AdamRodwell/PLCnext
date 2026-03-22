#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "UtilsComponent.hpp"

namespace Utils
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(Utils::UtilsComponent)
class UtilsProgram : public ProgramBase, private Loggable<UtilsProgram>
{
public: // typedefs

public: // construction/destruction
    UtilsProgram(Utils::UtilsComponent& utilsComponentArg, const String& name);
    UtilsProgram(const UtilsProgram& arg) = delete;
    virtual ~UtilsProgram() = default;

public: // operators
    UtilsProgram&  operator=(const UtilsProgram& arg) = delete;

public: // properties

public: // operations
    void    Execute() override;

public: /* Ports
           =====
           Ports are defined in the following way:
           //#port
           //#attributes(Input|Retain)
           //#name(NameOfPort)
           boolean portField;

           The attributes comment define the port attributes and is optional.
           The name comment defines the name of the port and is optional. Default is the name of the field.
        */

private: // fields
    Utils::UtilsComponent& utilsComponent;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline UtilsProgram::UtilsProgram(Utils::UtilsComponent& utilsComponentArg, const String& name)
: ProgramBase(name)
, utilsComponent(utilsComponentArg)
{
}

} // end of namespace Utils
