#ifndef _LOGINSERVER_H
#define _LOGINSERVER_H

#include <map>
#include <string>

#include "../common/src/typedefs.hpp"
#include "../player/forward.hpp"

class LoginServer
{
private:
	std::map<std::string, PlayerPtr> sessionMap;
};

#endif // _LOGINSERVER_H
