#pragma once

#define NON_COPYABLE(thistype)																	\
	public:																						\
	thistype(const thistype&) = delete;															\
	thistype& operator= (const thistype&) = delete;												\
	private:

#define SINGLETON_DEFCTOR(thistype)                                                             \
    public:                                                                                     \
    static thistype& GetInstance() {                                                            \
        static thistype instance; return instance; }                                            \
    NON_COPYABLE(thistype)                                                                      \
    private:                                                                                    \
    thistype() = default;                                                                           