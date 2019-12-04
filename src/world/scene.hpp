#ifndef _SCENE_H
#define _SCENE_H

#include <Eigen/Dense>
#include <set>

#include "forward.hpp"
#include "../common.hpp"

class Vortex
{
public:
	std::string destinationName;
	Eigen::Vector3f destinationPosition;
	Byte id;
};

class Scene
{
public:
	std::string name;
	std::set<Vortex> vortexes;
};

#endif // _SCENE_H
