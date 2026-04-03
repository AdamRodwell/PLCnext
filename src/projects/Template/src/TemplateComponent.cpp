#include "TemplateComponent.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "TemplateLibrary.hpp"

namespace Template
{
#if ARP_ABI_VERSION_MAJOR < 2
TemplateComponent::TemplateComponent(IApplication& application, const String& name)
: ComponentBase(application, ::Template::TemplateLibrary::GetInstance(), name, ComponentCategory::Custom)
    , programProvider(*this)
    , ProgramComponentBase(::Template::TemplateLibrary::GetInstance().GetNamespace(), programProvider)
#else
TemplateComponent::TemplateComponent(ILibrary& library, const String& name)
    : ComponentBase(library, name, ComponentCategory::Custom, GetDefaultStartOrder())
    , programProvider(*this)
    , ProgramComponentBase(::Template::TemplateLibrary::GetInstance().GetNamespace(), programProvider)
#endif
{
}

void TemplateComponent::Initialize()
{
    // never remove next line
    ProgramComponentBase::Initialize();

    // subscribe events from the event system (Nm) here
}

void TemplateComponent::LoadConfig()
{
    // load project config here
}

void TemplateComponent::SetupConfig()
{
    // never remove next line
    ProgramComponentBase::SetupConfig();

    // setup project config here
}

void TemplateComponent::ResetConfig()
{
    // never remove next line
    ProgramComponentBase::ResetConfig();

    // implement this inverse to SetupConfig() and LoadConfig()
}

void TemplateComponent::PowerDown()
{
	// implement this only if data shall be retained even on power down event
	// will work only for PLCnext controllers with an "Integrated uninterruptible power supply (UPS)"
	// Available with 2021.6 FW
}

} // end of namespace Template
