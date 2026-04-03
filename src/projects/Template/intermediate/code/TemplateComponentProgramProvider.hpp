#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramProviderBase.hpp"

namespace Template
{

using namespace Arp;
using namespace Arp::Plc::Commons::Esm;

//forwards
class TemplateComponent;

class TemplateComponentProgramProvider : public ProgramProviderBase
{

public:   // construction/destruction
    TemplateComponentProgramProvider(TemplateComponent& templateComponentArg);
#if ARP_ABI_VERSION_MAJOR < 2
    virtual ~TemplateComponentProgramProvider() = default;
#endif

public:   // IProgramProvider operations
    IProgram::Ptr CreateProgramInternal(const String& programName, const String& programType) override;

#if ARP_ABI_VERSION_MAJOR < 2
private:   // deleted methods
    TemplateComponentProgramProvider(const TemplateComponentProgramProvider& arg) = delete;
    TemplateComponentProgramProvider& operator=(const TemplateComponentProgramProvider& arg) = delete;
#endif

private: // fields
    TemplateComponent& templateComponent;
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class TemplateComponentProgramProvider

#if ARP_ABI_VERSION_MAJOR < 2
inline TemplateComponentProgramProvider::TemplateComponentProgramProvider(TemplateComponent& templateComponentArg)
    : templateComponent(templateComponentArg)
{
}
#endif
} // end of namespace Template
