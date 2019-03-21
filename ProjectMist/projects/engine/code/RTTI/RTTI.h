#pragma once

#include <Libraries/Containers.h>

namespace ME
{
    class RTTI
    {
    public:
        using Hash = size_t;
        RTTI(const std::string& name = "", Hash type = 0) :
            mTypename(name), mTypehash(type) {}
        bool operator< (const RTTI& rhs) const { return mTypehash < rhs.mTypehash; }

        String mTypename;
        Hash mTypehash = 0;
    };

    class RTTISystem
    {
    public:
        template <typename T>
        static RTTI& RegisterRTTI()
        {
            auto hash = typeid(T).hash_code();
            auto str = typeid(T).name();
            auto& rtti = GetRTTIsByName()[str];
            rtti = { str, hash};
            GetRTTIsByHash()[hash] = rtti;
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

    private:
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
}

#define RTTI_DECLARATION(thistype)																                    \
	public:																						                    \
	virtual FTF_RTTI& GetRTTI() const override {return smRTTI;}									                    \
	static const FTF_RTTI& sGetRTTI() {return smRTTI;}											                    \
	private: static FTF_RTTI& smRTTI;															                    \

#define RTTI_IMPLEMENTATION(thistype)															                    \
	FTF_RTTI& thistype::smRTTI = FTF_RTTISystem::RegisterRTTI<thistype>(thistype::CreateBase, thistype::CreateRP);	\