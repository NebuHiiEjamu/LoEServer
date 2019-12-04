#include <algorithm>
#include <boost/endian/conversion.hpp>
#include <iterator>
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

ByteBuffer&& ByteBuffer::clone(std::size_t bytes) const
{
	ByteBuffer newBuffer;
	newBuffer.data.insert(std::back_inserter(data), position, position + bytes);
	return std::move(newBuffer);
}

ByteString& ByteBuffer::getBytes() const
{
	return data;
}

std::size_t ByteBuffer::getSize() const
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

template <class StringType> StringType&& ByteBuffer::read(std::size_t bytes)
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

void ByteBuffer::readNull(std::size_t bytes)
{
	position += bytes;
}

template <class StringType> void ByteBuffer::write(const StringType &s);
{
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

template <> void ByteBuffer::write(const Timestamp &time, bool reverseEndian = false)
{
}

void ByteBuffer::write32(uint32 i)
{
	data.push_back(static_cast<Byte>((i & 0xFF000000) >> 24);
	data.push_back(static_cast<Byte>((i & 0xFF0000) >> 16);
	data.push_back(static_cast<Byte>((i & 0xFF00) >> 8);
	data.push_back(static_cast<Byte>(i & 0xFF);
}

void ByteBuffer::writeNull(std::size_t bytes)
{
	for (std::size_t i = 0; i < bytes; i++) data.push_back(0);
}
