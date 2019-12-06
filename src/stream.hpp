#ifndef _LOE_STREAM_H
#define _LOE_STREAM_H

#include <string>

#include "common/stream.hpp"

class GameInStream : public InStream
{
public:
	float read(bool, bool);
	std::string&& read();
};

class GameOutStream : public InStream
{
public:
	template <> void write(const std::string&);
	void write(float, bool, bool);
};

#endif // _LOE_STREAM_H
