#ifndef _WORLDSERVER_H
#define _WORLDSERVER_H

#include <set>

#include "forward.hpp"
#include "../player/forward.hpp"
#include "../net/forward.hpp"
#include "../common.hpp"

class WorldServer final : std::enable_shared_from_this<WorldServer>
{
public:
	static WorldServerRef getInstance();
private:
	WorldServer();
private:
	static std::shared_ptr<WorldServer> worldServer;
	GameConnectionPtr<boost::asio::ip::udp> udpConnection;
	GameConnectionPtr<boost::asio::ip::tcp> remote;
};

#endif // _WORLDSERVER_H
