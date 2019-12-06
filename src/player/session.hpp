#ifndef _SESSION_H
#define _SESSION_H

#include <array>
#include <openssl/sha.h>

#include "forward.hpp"
#include "../common/src/typedefs.hpp"

enum class InGameStatus : Byte
{
	notInGame = 0,
	characterSelect,
	instantiated,
	inGame
};

template <class T>
class Session : public std::enable_shared_from_this<Session<T>>
{
private:
	GameConnectionPtr<T> connection;
	PlayerPtr player;
	std::string userName;
	std::array<Byte, SHA_DIGEST_LENGTH> passwordHash;
	InGameStatus inGame;
};

#endif // _SESSION_H
