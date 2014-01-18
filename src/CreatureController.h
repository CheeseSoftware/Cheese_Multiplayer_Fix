#pragma once

#include <string>
#include <memory>

class Creature;

class CreatureController
{
	const int m_id;
	std::string m_name;

	std::unique_ptr<Creature> m_boundedCreature;
	
public:
	CreatureController(int id);
	std::unique_ptr<Creature> &&SetCreature(std::unique_ptr<Creature> &&creature);
};