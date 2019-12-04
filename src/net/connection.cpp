#include <functional>

#include "connection.hpp"
#include "hive.hpp"

using boost::asio;

template <class T>
Connection<T>::Connection(HivePtr hive)
	hive(hive),
	socket(hive->getIOContext()),
	strand(hive->getIOContext()),
	errorState(0)
{
}

template <class T>
HivePtr Connection<T>::getHive()
{
	return hive;
}

template <class T>
Strand& Connection<T>::getStrand()
{
	return strand;
}

template <class T>
Conmection<T>::Socket& Connection<T>::getSocket()
{
	return socket;
}

template <class T>
bool Connection<T>::hasError()
{
	uint32 v1 = 1;
	uint32 v2 = 1;
	return errorState.compare_exchange_strong(v1, v2);
}

template <class T>
void Connection<T>::disconnect()
{
	onDisconnect();
	socket.close();
}

template <class T>
void Connection<T>::startError(Error error)
{
	uint32 v1 = 1;
	uint32 v2 = 0;

	if (!errorState.compare_exchange_strong(v1, v2))
	{
		Error errorCode;

		socket.shutdown(Socket::shutdown_both, errorCode);
		socket.close(errorCode);
		onError(error);
	}
}

template <class T>
void Connection<T>::dispatchReceive(Size totalBytes)
{
	pendingReceives.push_back(totalBytes);
	if (pendingReceives.empty()) startReceive(totalBytes);
}

template <class T>
void Connection<T>::startReceive(Size totalBytes)
{
	if (totalBytes > 0)
	{
		inBuffer.resize(totalBytes);
		asio::async_read(socket, asio::buffer(inBuffer), asio::bind_executor(strand,
			std::bind(&Connection<T>::handleReceive, shared_from_this(), std::placeholders::_1,
				std::placeholders::_2)));
	}
	else
	{
		inBuffer.resize(inBufferSize);
		asio::async_read_some(socket, asio::buffer(inBuffer), asio::bind_executor(strand,
			std::bind(&Connection<T>::handleReceive, shared_from_this(), std::placeholders::_1,
				std::placeholders::_2)));
	}
}

template <class T>
void Connection<T>::handleReceive(Error error, Size receivedBytes)
{
	if (error || hasError() || hive->stopped()) startError(error);
	else
	{
		inBuffer.resize(receivedBytes);
		onReceive(inBuffer);
		receive();
		pendingReceives.pop();
		if (!pendingReceives.empty()) startReceive(pendingReceives.front());
	}
}

template <class T>
void Connection<T>::receive(Size totalBytes = 0)
{
	strand.post(std::bind(&Connection<T>::dispatchReceive, shared_from_this(), totalBytes));
}

template <class T>
std::uint32_t Connection<T>::getInBufferSize() const
{
	return inBufferSize;
}

template <class T>
void Connection<T>::setInBufferSize(Size newSize)
{
	inBufferSize = newSize;
}

template <class T>
void Connection<T>::onConnect(std::string_view, uint16)
{
}

template <class T>
void Connection<T>::onSend(const ByteString&)
{
}

template <class T>
void Connection<T>::onReceive(const ByteString&)
{
}

template <class T>
void Connection<T>::onError(Error)
{
}

template <class T>
void Connection<T>::onDisconnect()
{
}
