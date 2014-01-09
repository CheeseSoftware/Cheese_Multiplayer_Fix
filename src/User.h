#pragma once

#include <string>
#include <memory>

#include "Creature.h"

//class Creature;

class User
{
	const int m_id;
	std::string m_name;
	std::weak_ptr<Creature> m_boundedCreature;
	
public:
	User(int id);

	void SetCreature(Creature *creature);
};