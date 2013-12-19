#pragma once

class GameUtility;
class Chunk;


class IGenerator
{
public:
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility)=0;
};