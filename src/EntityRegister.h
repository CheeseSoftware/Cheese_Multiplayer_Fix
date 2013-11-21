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
	void RegisterEntity(TextureContainer tC, const Entity *entity, const size_t typeId);
	Entity *getEntityType(const unsigned short id, const unsigned short metadata);
	Entity *getEntityTypeByTypeId(const size_t typeId, const unsigned short metadata);
};