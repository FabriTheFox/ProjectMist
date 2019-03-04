#pragma once

#define NON_COPYABLE(thistype)																	\
	public:																						\
	thistype(const thistype&) = delete;															\
	thistype& operator= (const thistype&) = delete;												\
	thistype() = default; private:

#define SINGLETON_NO_CTOR(thistype)                                                             \
    public:                                                                                     \
    static const thistype& GetInstance() {                                                      \
        static thistype instance; return instance; }                                            \
    NON_COPYABLE(thistype)