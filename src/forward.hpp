#ifndef _FORWARD_H
#define _FORWARD_H

#include <memory>

template <class T> class GameConnection;

template <class T> using GameConnectionPtr = std::shared_ptr<GameConnection<T>>;

#endif // _FORWARD_H
