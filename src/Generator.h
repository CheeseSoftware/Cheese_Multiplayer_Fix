#include <noise\noise.h>

class GameUtility;
class Chunk;

//class Chunk;

struct Generator
{
protected:
	noise::module::Perlin noiseModule;
	/*RANDOM-generator och sånt*/
public:
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility)=0;
};

struct StandardGenerator : Generator
{
public:
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
};