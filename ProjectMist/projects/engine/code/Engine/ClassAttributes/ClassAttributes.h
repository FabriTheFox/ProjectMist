#pragma once

#define NON_COPYABLE(thistype)																	\
	public:																						\
	thistype(const thistype&) = delete;															\
	thistype& operator= (const thistype&) = delete;												\
	private:
