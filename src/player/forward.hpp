#ifndef _PLAYER_FORWARD_H
#define _PLAYER_FORWARD_H

#include <memory>

template <class T> class GameConnection;
class Player;
class Pony;
class PonyData;
template <class T> class Session;

template <class T> using GameConnectionPtr = std::shared_ptr<GameConnection<T>>;
using PlayerPtr = std::shared_ptr<Player<T>>;
using PlayerRef = std::weak_ptr<Player<T>>;
template <class T> using SessionPtr = std::shared_ptr<Session<T>>;
template <class T> using SessionRef = std::weak_ptr<Session<T>>;

#endif // _PLAYER_FORWARD_H
