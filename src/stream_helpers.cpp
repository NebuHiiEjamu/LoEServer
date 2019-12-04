#include <codecvt>
#include <cstdint>
#include <locale>
#include <utility>

#include "stream_helpers.hpp"

std::string&& readString(std::istream &stream)
{
	static std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> stringCodec;
	std::uint8_t byte2 = 0;
	std::uint8_t byte1 = static_cast<std::uint8_t>(stream.get());

	if (byte1 >= 128) byte2 = static_cast<std::uint8_t>(stream.get());
	std::uint16_t textSize = (byte1 % 128) + (byte2 * 128);

	std::u16string original(textSize, 0);
	stream.read(reinterpret_cast<char*>(original.data()), textSize * 2);

	return converter.to_bytes(original);
}

void writeString(std::ostream &stream, std::string_view value)
{
	if (value.size() > 128)
	{
		std::uint16_t textSize = value.size();
		stream.write(reinterpret_cast<const char*>(&textSize), 2);
	}
	else
	{
		std::uint8_t textSize = value.size();
		stream.put(static_cast<char>(textSize));
	}

	stream.write(value.data(), value.size());
}
