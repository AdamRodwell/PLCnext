#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "TemplateComponent.hpp"

namespace Template
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(Template::TemplateComponent)
class TemplateProgram : public ProgramBase, private Loggable<TemplateProgram>
{
public: // typedefs

public: // construction/destruction
    TemplateProgram(Template::TemplateComponent& templateComponentArg, const String& name);
#if ARP_ABI_VERSION_MAJOR < 2
    TemplateProgram(const TemplateProgram& arg) = delete;
    virtual ~TemplateProgram() = default;
#endif

public: // operators
#if ARP_ABI_VERSION_MAJOR < 2
    TemplateProgram&  operator=(const TemplateProgram& arg) = delete;
#endif

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
    Template::TemplateComponent& templateComponent;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline TemplateProgram::TemplateProgram(Template::TemplateComponent& templateComponentArg, const String& name)
: ProgramBase(name)
, templateComponent(templateComponentArg)
{
}

} // end of namespace Template
