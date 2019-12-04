#ifndef _STREAM_HELPERS_H
#define _STREAM_HELPERS_H

#include <istream>
#include <ostream>
#include <string>

std::string&& readString(std::istream&);
void writeString(std::ostream&, std::string_view);

#endif // _STREAM_HELPERS_H
