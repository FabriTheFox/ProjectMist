#pragma once

#include <Libraries/Containers.h>
#include <Libraries/Memory.h>

// Needs to inherit from IDynamic. Do not use with abstract classes
#define RTTI_DECLARATION(thistype)																        \
	public:																						        \
	virtual const ME::RTTI& GetRTTI() const {return sm_RTTI;}									        \
	static const ME::RTTI& sGetRTTI() {return sm_RTTI;}											        \
	private: static const ME::RTTI& sm_RTTI;				                                            \

#define RTTI_DECLARATION_DLL(thistype, dll)															    \
	public:																						        \
	virtual const ME::RTTI& GetRTTI() const {return sm_RTTI;}									        \
	static const ME::RTTI& sGetRTTI() {return sm_RTTI;}											        \
	private: dll static const ME::RTTI& sm_RTTI;				                                        \

#define RTTI_IMPLEMENTATION(thistype)													\
	const ME::RTTI& thistype::sm_RTTI = ME::RTTISystem::RegisterRTTI<thistype>();	    \

#define RTTI_IMPLEMENTATION_TEMPLATE_1(thistype, t0)                                    \
        template <typename t0>                                                          \
        const RTTI& thistype<t0>::sm_RTTI = RTTISystem::RegisterRTTI<thistype<t0>>();   \

#define RTTI_IMPLEMENTATION_TEMPLATE_2(thistype, t0, t1)                                        \
        template <typename t0, typename t1>                                                     \
        const RTTI& thistype<t0, t1>::sm_RTTI = RTTISystem::RegisterRTTI<thistype<t0, t1>>();   \

#define RTTI_IMPLEMENTATION_TEMPLATE_3(thistype, t0, t1, t2)                                            \
        template <typename t0, typename t1, typename t2>                                                \
        const RTTI& thistype<t0, t1, t2>::sm_RTTI = RTTISystem::RegisterRTTI<thistype<t0, t1, t2>>();   \

#define GET_MACRO(_1, _2, _3, NAME, ...) NAME
#define EXPAND(x) x
#define RTTI_IMPLEMENTATION_TEMPLATE(thistype, ...) EXPAND(GET_MACRO(__VA_ARGS__, RTTI_IMPLEMENTATION_TEMPLATE_3, RTTI_IMPLEMENTATION_TEMPLATE_2, RTTI_IMPLEMENTATION_TEMPLATE_1)(thistype, __VA_ARGS__))

namespace ME
{
    class IDynamic;

    class RTTI
    {
    public:
        using Hash = size_t;
        typedef IDynamic*(*CreatorFuncRaw)();
        typedef UPtr<IDynamic>(*CreatorFuncUnique)();

        RTTI(const String& name = "", Hash type = 0, CreatorFuncRaw creator = nullptr) :
            m_Typename(name), m_Typehash(type), mCreatorRaw(creator){}

        bool operator< (const RTTI& rhs) const { return m_Typehash < rhs.m_Typehash; }
        bool operator== (const RTTI& rhs) const { return m_Typehash == rhs.m_Typehash; }

        template<typename T>
        T* CreateRawAs() const { return reinterpret_cast<T*>(mCreatorRaw()); }

        template<typename T>
        UPtr<T> CreateUniqueAs() const { return ME::UPtr<T>{static_cast<T*>(mCreatorUnique().release())};}

        String m_Typename;
        Hash m_Typehash = 0;
        CreatorFuncRaw mCreatorRaw{ nullptr };
        CreatorFuncUnique mCreatorUnique{ nullptr };
    };

    class RTTISystem
    {
    public:
        template <typename T>
        static RTTI& RegisterRTTI()
        {
            auto str = typeid(T).name();
            auto& rtti = GetRTTIsByName()[str];

            rtti.m_Typehash = typeid(T).hash_code();;
            rtti.m_Typename = str;
            rtti.mCreatorRaw = [](){return static_cast<IDynamic*>((new T())); };
            rtti.mCreatorUnique = [](){ return static_cast<UPtr<IDynamic>>(std::make_unique<T>()); };

            GetRTTIsByHash()[rtti.m_Typehash] = rtti;
            return rtti;
        }

        static const RTTI& GetRTTI(const String& name)
        {
            return GetRTTIsByName().find(name)->second;
        }

        static const RTTI& GetRTTI(const RTTI::Hash& hash)
        {
            return GetRTTIsByHash().find(hash)->second;
        }

        static UnorderedMap<String, RTTI>& GetRTTIsByName()
        {
            static UnorderedMap<String, RTTI> map;
            return map; 
        }

        static UnorderedMap<RTTI::Hash, RTTI>& GetRTTIsByHash()
        {
            static UnorderedMap<RTTI::Hash, RTTI> map;
            return map;
        }
    };

    class IDynamic
    {
    public:
        virtual const RTTI& GetRTTI() const = 0;
    protected:
    };
}

// Compatibility with std unordered containers
namespace std
{
    template <>
    class hash<ME::RTTI> {
    public:
        size_t operator()(const ME::RTTI & rtti) const
        {
            return rtti.m_Typehash;
        }
    };
};