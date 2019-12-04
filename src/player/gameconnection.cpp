#include "gameconnection.hpp"
#include "net/hive.hpp"

template <class T>
GameConnection<T>::GameConnection(HivePtr hive):
	Connection(hive)
{
}

template <class T>
void GameConnection<T>::onConnect(std::string_view, uint16)
{
}

template <class T>
void GameConnection<T>::onSend(const ByteString&)
{
}

template <class T>
void GameConnection<T>::onReceive(const ByteString&)
{
}

template <class T>
void GameConnection<T>::onError(Error)
{
}

template <class T>
void GameConnection<T>::onDisconnect()
{
}
