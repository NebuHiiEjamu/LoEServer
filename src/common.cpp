#include <algorithm>
#include <boost/endian/conversion.hpp>
#include <codecvt>
#include <iterator>
#include <locale>
#include <utility>

#include "common.hpp"

ByteBuffer::ByteBuffer()
	position(data.begin())
{
}

ByteBuffer::ByteBuffer(ByteString &inString):
	data(std::move(inString)),
	position(data.begin())
{
}

ByteBuffer&& ByteBuffer::clone(Size bytes) const
{
	ByteBuffer newBuffer;
	newBuffer.data.insert(std::back_inserter(data), position, position + bytes);
	return std::move(newBuffer);
}

ByteString& ByteBuffer::getBytes() const
{
	return data;
}

Size ByteBuffer::getSize() const
{
	return data.size();
}

void ByteBuffer::setBytes(ByteString &inString)
{
	data = std::move(inString);
}

void ByteBuffer::flush()
{
	data.clear();
}

template <class StringType> StringType&& ByteBuffer::read(Size bytes)
{
	StringType s(position, position + bytes);
	position += bytes;
	return std::move(s);
}

float ByteBuffer::read(bool half = false, bool reverseEndian = false)
{
	float f;
	if (half)
	{
		uint16 half;
		std::copy(position, position + sizeof(uint16), reinterpret_cast<Byte*>(&half));
		position += sizeof(uint16);
		if (reverseEndian) half = boost::endian::endian_reverse(half);
		half = (half & 0xFFFF) << 16;
		f = *reinterpret_cast<float*>(&half);
	}
	else
	{
		if (reverseEndian)
		{
			uint32 i;
			std::copy(position, position + sizeof(uint32), reinterpret_cast<uint32*>(&i));
			i = boost::endian::endian_reverse(i);
			f = *reinterpret_cast<float*>(&i);
		}
		else
			std::copy(position, position + sizeof(float), reinterpret_cast<Byte*>(&f));
		position += sizeof(float);
	}

	return f;
}

template <class T> T ByteBuffer::read(bool reverseEndian = false)
{
	T t;
	std::copy(position, position + sizeof(T), reinterpret_cast<Byte*>(&t));
	position += sizeof(T);
	if (reverseEndian) boost::endian::endian_reverse(t);
	return t;
}

std::string&& ByteBuffer::read()
{
	static std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
	Byte byte2 = 0;
	Byte byte1 = read();

	if (byte1 >= 128) byte2 = read();
	Size length = (byte1 % 128) + (byte2 * 128);
	std::u16string original = read(length * 2);

	return converter.to_bytes(original);
}

void ByteBuffer::readNull(Size bytes)
{
	position += bytes;
}

template <class StringType> void ByteBuffer::write(const StringType &s);
{
	data.insert(std::back_inserter(data), s.begin(), s.end());
}

template <> void ByteBuffer::write(const std::string &s)
{
	if (s.size() >= 128) write16(s.size());
	else data.push_back(s.size());
	data.insert(std::back_inserter(data), s.begin(), s.end());
}

template <class T> void ByteBuffer::write(T t, bool reverseEndian = false)
{
	if (reverseEndian)
		for (int i = sizeof(T) - 1; i >= 0; i--)
			data.push_back(static_cast<Byte>((t & (0xFF << (i * 8))) >> (i * 8)));
	else
		for (int i = 0; i < sizeof(T); i++)
			data.push_back(static_cast<Byte>((t & (0xFF << (i * 8))) >> (i * 8)));
}

void ByteBuffer::write(float f, bool half = false, bool reverseEndian = false)
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

void ByteBuffer::writeNull(Size bytes)
{
	for (std::size_t i = 0; i < bytes; i++) data.push_back(0);
}
