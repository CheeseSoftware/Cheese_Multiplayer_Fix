#pragma once

#include <string>
#include <map>
#include <functional>

class TextureContainer;
class Entity;
#include "EventHandler.h"//template<class T> class EventHandler;

class EntityRegister
{
	std::map<size_t, std::function<Entity*(EventHandler*)>> blockTypeList;
public:
	EntityRegister();
	void RegisterEntity(TextureContainer tC, Entity *entity, size_t typeId);
	Entity *getEntityType(unsigned short id, unsigned short metadata);
	Entity *getEntityTypeByTypeId(size_t typeId, unsigned short metadata);
};