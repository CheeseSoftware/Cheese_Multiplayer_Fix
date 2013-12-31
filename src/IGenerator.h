#pragma once

class GameUtility;
class Chunk;

namespace generator
{
	class IGenerator
	{
	public:
		virtual Chunk *operator() (long x, long y, GameUtility *gameUtility)=0;
	};
}