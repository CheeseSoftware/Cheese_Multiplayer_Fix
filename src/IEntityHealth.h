#include "Entity.h"

class IEntityHearlth : virtual Entity
{
protected:
	float health;
public:
	virtual void OnDamage(float);
};