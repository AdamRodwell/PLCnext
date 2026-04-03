#include "TemplateComponentProgramProvider.hpp"
#include "TemplateProgram.hpp"

namespace Template
{

#if ARP_ABI_VERSION_MAJOR < 2
#else
TemplateComponentProgramProvider::TemplateComponentProgramProvider(TemplateComponent& templateComponentArg)
    : templateComponent(templateComponentArg)
{
}

#endif
IProgram::Ptr TemplateComponentProgramProvider::CreateProgramInternal(const String& programName, const String& programType)
{
    if (programType == "TemplateProgram")
    { 
        return std::make_shared<::Template::TemplateProgram>(this->templateComponent, programName);
    }

    // else unknown program
    return nullptr;
}

} // end of namespace Template
