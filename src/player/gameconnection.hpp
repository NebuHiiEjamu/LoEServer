#ifndef _GAMECONNECTION_H
#define _GAMECONNECTION_H

#include "forward.hpp"
#include "../net/connection.hpp"

template <class T>
class GameConnection : public Connection<T>
{
public:
	GameConnection(HivePtr);
protected:
	void onConnect(std::string_view, uint16) override;
	void onSend(const ByteString&) override;
	void onReceive(const ByteString&) override;
	void onError(Error) override;
	void onDisconnect() override;
private:
	SessionRef session;
};

#endif // _GAMECONNECTION_H
