#ifndef _COMMON_H
#define _COMMON_H

#include <boost/asio.hpp>
#include <chrono>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>

using Byte = std::uint8_t;
using ByteString = std::vector<Byte>;
using Error = boost::asio::error_code;
using int16 = std::int16_t;
using int32 = std::int32_t;
using LockGuard = std::lock_guard<std::mutex>;
using Size = std::size_t;
using Strand = boost::asio::io_context::strand;
using Timestamp = std::chrono::time_point<std::chrono::system_clock>;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;

class ByteBuffer : std::enable_shared_from_this<ByteBuffer>
{
public:
	ByteBuffer();
	ByteBuffer(ByteString&);
	ByteBuffer&& clone(std::size_t) const;
	ByteString& getBytes() const;
	void setBytes(ByteString&);
	Size getSize() const;
	void flush();
	template <class StringType> StringType&& read(Size);
	template <class T> T read(bool);
	float read(bool, bool);
	template <> Timestamp&& read(bool);
	template <> std::string&& read(bool);
	void readNull(Size);
	template <class T> void write(T, bool);
	template <> void write(const Timestamp&, bool);
	template <> void write(const std::string&, bool);
	void write32(uint32); // for ambiguity
	void writeNull(Size);
private:
	ByteString data;
	ByteString::iterator position;
};

using ByteBufferPtr = std::shared_ptr<ByteBuffer>;

#endif // _COMMON_H
