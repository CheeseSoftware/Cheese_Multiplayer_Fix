#pragma once
#include "block.h"

class UniqueBlock : public virtual Block
{
public:
	virtual bool isUnique() const;
};