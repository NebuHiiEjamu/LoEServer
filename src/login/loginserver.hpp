#ifndef _LOGINSERVER_H
#define _LOGINSERVER_H

#include <boost/asio.hpp>
#include <map>
#include <string>

#include "../player/forward.hpp"

using boost::asio;

class LoginServer
{
private:
	std::map<std::string, PlayerPtr> sessionMap;
};

#endif // _LOGINSERVER_H
