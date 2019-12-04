#ifndef _COMPONENTS_H
#define _COMPONENTS_H

#include "common.hpp"

class StatsComponent
{
	virtual void kill() = 0;
	virtual void respawn() = 0;
	virtual void damage(uint32) = 0;
public:
	float health;
};

#endif // _COMPONENTS_H
