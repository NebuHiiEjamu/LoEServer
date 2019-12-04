#include "worldserver.hpp"

WorldServer::worldServer = make_shared<WorldServer>();

WorldServerRef WorldServer::getInstance()
{
	return worldServer;
}
