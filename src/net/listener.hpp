#ifndef _LISTENER_H
#define _LISTENER_H

#include <atomic>

#include "forward.hpp"
#include "../common.hpp"

template <class T>
class Listener : public std::enable_shared_from_this<Listener>
{
public:
	using Acceptor = T::acceptor;
	using Endpoint = T::endpoint;
	using Resolver = T::resolver;

	Listener(HivePtr);
	HivePtr getHive();
	Acceptor& getAcceptor();
	Strand& getStrand();
	bool hasError();
	void listen(std::string_view, uint16);
	void accept(ConnectionPtr<T>);
	void stop();
private:
	void dispatchAccept(ConnectionPtr<T>);
	void handleAccept(Error, ConnectionPtr<T>);
protected:
	virtual bool onAccept(ConnectionPtr<T>, std::string_view, uint16);
	virtual void onError(Error);
protected:
	HivePtr hive;
	Acceptor acceptor;
	Strand strand;
	std::atomic_uint32_t errorState;
};

#endif // _LISTENER_H
