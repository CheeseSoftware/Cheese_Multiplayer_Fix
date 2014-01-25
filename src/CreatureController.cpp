#include "CreatureController.h"
#include "Creature.h"

CreatureController::CreatureController(int id, std::string name)
	: m_id(id)
	, m_name(name)
	, m_boundedCreature(nullptr)
{
}

std::unique_ptr<Creature> &&CreatureController::SetCreature(std::unique_ptr<Creature> &&creature)
{
	std::unique_ptr<Creature> old = std::move(m_boundedCreature);

	m_boundedCreature = std::move(creature);

	//m_boundedCreature->setController(this);

	return std::move(old);
}