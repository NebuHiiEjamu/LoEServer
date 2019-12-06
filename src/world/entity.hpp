#ifndef _ENTITY_H
#define _ENTITY_H

#include <Eigen/Dense>

#include "forward.hpp"
#include "../common/src/typedefs.hpp"

struct Entity : public std::enable_shared_from_this<Entity>
{
	std::string model;
	std::string scene;
	Eigen::Vector3f position;
	Eigen::Quaternionf rotation;
	uint16 id;
	uint16 netviewId;
};

#endif // _ENTITY_H
