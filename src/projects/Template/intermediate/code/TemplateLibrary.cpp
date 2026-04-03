#include "TemplateLibrary.hpp"
#if ARP_ABI_VERSION_MAJOR < 2
#include "Arp/System/Core/CommonTypeName.hxx"
#else
#include "Arp/Base/Core/CommonTypeName.hxx"
#include "TemplateLibraryInfo.hpp"
#endif
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "TemplateComponent.hpp"

namespace Template
{

#if ARP_ABI_VERSION_MAJOR < 2
TemplateLibrary::TemplateLibrary(AppDomain& appDomain)
    : MetaLibraryBase(appDomain, ARP_VERSION_CURRENT, typeDomain)
    , typeDomain(CommonTypeName<TemplateLibrary>().GetNamespace())
#else
TemplateLibrary::TemplateLibrary()
    : MetaLibraryBase(TemplateLibraryVersion, typeDomain)
    , typeDomain(CommonTypeName<TemplateLibrary>().GetNamespace())
#endif
{
#if ARP_ABI_VERSION_MAJOR < 2
    this->componentFactory.AddFactoryMethod(CommonTypeName<::Template::TemplateComponent>(), &::Template::TemplateComponent::Create);
#else
 
    this->AddComponentType<::Template::TemplateComponent>();
#endif
    this->InitializeTypeDomain();
}

#if ARP_ABI_VERSION_MAJOR < 2
void TemplateLibrary::Main(AppDomain& appDomain)
{
    SingletonBase::CreateInstance(appDomain);
}
#else
TemplateLibrary& TemplateLibrary::GetInstance()
{
    static TemplateLibrary instance;
    return instance;
}
#endif


#if ARP_ABI_VERSION_MAJOR < 2
extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain)
{
    TemplateLibrary::Main(appDomain);
    return  TemplateLibrary::GetInstance();
}
} // end of namespace Template
#else
} // end of namespace Template
extern "C" ARP_EXPORT Arp::Base::Acf::Commons::ILibrary& Template_MainEntry()
{
    return  Template::TemplateLibrary::GetInstance();
}
#endif

