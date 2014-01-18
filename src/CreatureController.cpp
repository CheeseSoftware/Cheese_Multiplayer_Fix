#include "CreatureController.h"
#include "Creature.h"

CreatureController::CreatureController(int id)
	: m_id(id)
{
}

std::unique_ptr<Creature> &&CreatureController::SetCreature(std::unique_ptr<Creature> &&creature)
{
	std::unique_ptr<Creature> old = std::move(m_boundedCreature);

	m_boundedCreature = std::move(creature);

	return std::move(old);
}