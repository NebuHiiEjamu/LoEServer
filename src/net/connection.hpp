#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <atomic>
#include <boost/asio.hpp>
#include <queue>
#include <string>
#include <vector>

#include "../common.hpp"
#include "forward.hpp"

template <class T>
class Connection : public std::enable_shared_from_this<Connection<T>>
{
public:
	using Socket = T::socket;

	Connection(HivePtr);
	HivePtr getHive();
	Strand& getStrand();
	Socket& getSocket();
	Size getInBufferSize() const;
	void setInBufferSize(Size);
	bool hasError();
	void disconnect();
	void receive(Size);
private:
	void dispatchReceive(Size);
	void startReceive(Size);
	void handleReceive(Error, Size);
	void startError(Error);
protected:
	virtual void onConnect(std::string_view, uint16);
	virtual void onSend(const ByteString&);
	virtual void onReceive(const ByteString&);
	virtual void onError(Error);
	virtual void onDisconnect();
protected:
	HivePtr hive;
	Socket socket;
	Strand strand;
	ByteString inBuffer;
	std::atomic_uint32_t errorState;
	std::queue<Size> pendingReceives;
	std::queue<ByteString> pendingSends;
	Size inBufferSize;
};

#endif // _CONNECTION_H
