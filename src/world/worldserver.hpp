#ifndef _WORLDSERVER_H
#define _WORLDSERVER_H

#include <set>

#include "forward.hpp"
#include "../player/forward.hpp"
#include "../common/src/typedefs.hpp"

class WorldServer final : std::enable_shared_from_this<WorldServer>
{
public:
	static WorldServerRef getInstance();
private:
	WorldServer();
private:
	static std::shared_ptr<WorldServer> instance;
	GameConnectionPtr<boost::asio::ip::udp> udpConnection;
	GameConnectionPtr<boost::asio::ip::tcp> remote;
};

#endif // _WORLDSERVER_H
