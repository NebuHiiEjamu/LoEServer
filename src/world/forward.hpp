#ifndef _WORLD_FORWARD_H
#define _WORLD_FORWARD_H

#include <memory>

class Entity;
class Scene;
class WorldServer;

using EntityPtr = std::shared_ptr<Entity>
using WorldServerRef = std::weak_ptr<WorldServer>;

#endif // _WORLD_FORWARD_H
