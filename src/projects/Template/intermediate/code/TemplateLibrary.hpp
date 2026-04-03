#pragma once
#include "Arp/System/Core/Arp.h"
#if ARP_ABI_VERSION_MAJOR < 2
#include "Arp/System/Core/AppDomain.hpp"
#include "Arp/System/Core/Singleton.hxx"
#include "Arp/System/Core/Library.h"
#endif
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeDomain.hpp"

namespace Template
{

#if ARP_ABI_VERSION_MAJOR < 2
using namespace Arp::System::Acf;
#else
using namespace Arp::Base::Acf::Commons;
#endif
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::Plc::Commons::Meta::TypeSystem;

class TemplateLibrary : public MetaLibraryBase
#if ARP_ABI_VERSION_MAJOR < 2
    , public Singleton<TemplateLibrary>
#endif
{
#if ARP_ABI_VERSION_MAJOR < 2
public: // typedefs
    typedef Singleton<TemplateLibrary> SingletonBase;
#else
    TemplateLibrary(void);
#endif
public: // construction/destruction
#if ARP_ABI_VERSION_MAJOR < 2
    TemplateLibrary(AppDomain& appDomain);
    virtual ~TemplateLibrary() = default;

public: // static operations (called through reflection)
    static void Main(AppDomain& appDomain);
#else
    static TemplateLibrary& GetInstance();
#endif

private: // methods
    void InitializeTypeDomain();

#if ARP_ABI_VERSION_MAJOR < 2
private: // deleted methods
    TemplateLibrary(const TemplateLibrary& arg) = delete;
    TemplateLibrary& operator= (const TemplateLibrary& arg) = delete;
#endif
private:  // fields
    TypeDomain typeDomain;
};

#if ARP_ABI_VERSION_MAJOR < 2
extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain);
#endif
///////////////////////////////////////////////////////////////////////////////
// inline methods of class TemplateLibrary

} // end of namespace Template
