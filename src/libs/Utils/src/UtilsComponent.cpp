#include "UtilsComponent.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "UtilsLibrary.hpp"

namespace Utils
{

UtilsComponent::UtilsComponent(IApplication& application, const String& name)
: ComponentBase(application, ::Utils::UtilsLibrary::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, ProgramComponentBase(::Utils::UtilsLibrary::GetInstance().GetNamespace(), programProvider)
{
}

void UtilsComponent::Initialize()
{
    // never remove next line
    ProgramComponentBase::Initialize();

    // subscribe events from the event system (Nm) here
}

void UtilsComponent::LoadConfig()
{
    // load project config here
}

void UtilsComponent::SetupConfig()
{
    // never remove next line
    ProgramComponentBase::SetupConfig();

    // setup project config here
}

void UtilsComponent::ResetConfig()
{
    // never remove next line
    ProgramComponentBase::ResetConfig();

    // implement this inverse to SetupConfig() and LoadConfig()
}

void UtilsComponent::PowerDown()
{
	// implement this only if data must be retained even on power down event
	// will work only for PLCnext controllers with an "Integrated uninterruptible power supply (UPS)"
	// Available with 2021.6 FW
}

} // end of namespace Utils
