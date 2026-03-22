#include "StarterKitComponentProgramProvider.hpp"
#include "StarterKitProgram.hpp"
#include "TemplateController.hpp"

namespace StarterKit
{

IProgram::Ptr StarterKitComponentProgramProvider::CreateProgramInternal(const String& programName, const String& programType)
{
    if (programType == "StarterKitProgram")
    { 
        return std::make_shared<::StarterKit::StarterKitProgram>(this->starterKitComponent, programName);
    }
    if (programType == "TemplateController")
    { 
        return std::make_shared<::StarterKit::TemplateController>(this->starterKitComponent, programName);
    }

    // else unknown program
    return nullptr;
}

} // end of namespace StarterKit
