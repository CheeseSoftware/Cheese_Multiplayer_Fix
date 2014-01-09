class Chunk;

class Compressor
{
public:
	static void *QuadTreeCompressChunk(Chunk *chunk);
	static Chunk *QuadTreeDecompressChunk(void *data);
};