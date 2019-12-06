#include <boost/endian/conversion.hpp>
#include <codecvt>
#include <locale>
#include <utility>

#include "common.hpp"

float GameInStream::read(bool half = false, bool reverseEndian = false)
{
	float f;
	if (half)
	{
		uint16 half;
		internal.read(reinterpret_cast<Byte*>(&half), sizeof(uint16));
		if (reverseEndian) half = boost::endian::endian_reverse(half);
		half = (half & 0xFFFF) << 16;
		f = *reinterpret_cast<float*>(&half);
	}
	else
	{
		if (reverseEndian)
		{
			uint32 i;
			internal.read(reinterpret_cast<Byte*>(&i), sizeof(uint32));
			i = boost::endian::endian_reverse(i);
			f = *reinterpret_cast<float*>(&i);
		}
		else
			internal.read(reinterpret_cast<Byte*>(&f), sizeof(float));
	}

	return f;
}

std::string&& GameInStream::read()
{
	static std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
	Byte byte2 = 0;
	Byte byte1 = read();

	if (byte1 >= 128) byte2 = read();
	Size length = (byte1 % 128) + (byte2 * 128);
	std::u16string original = read(length * 2);

	return converter.to_bytes(original);
}

template <> void GameOutStream::write(const std::string &s)
{
	if (s.size() >= 128) write16(s.size());
	else internal.put(s.size());
	internal.write(reinterpret_cast<const Byte*>(&s[0]), s.size());
}

void GameOutStream::write(float f, bool half = false, bool reverseEndian = false)
{
	if (half)
	{
		uint16 half = static_cast<uint16>((*reinterpret_cast<uint32*>(&f) & 0xFFFF0000) >> 16);
		if (reverseEndian) write(half, true);
		else write(half);
	}
	else
	{
		uint32 i = *reinterpret_cast<uint32*>(&f);
		if (reverseEndian) write(i, true);
		else write(i);
	}
}
