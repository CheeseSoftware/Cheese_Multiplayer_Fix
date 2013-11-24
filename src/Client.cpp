#include "Client.h"

Client::Client()
{
	#ifdef _SERVER
	chunks = new bool[11*16];
	for(int x = 0; x < 11; x++)
	{

			chunks[x] = false;
	}
#endif
	socket = new sf::TcpSocket();
	isMeasuringPing = false;
	pingClock.restart();
}

Client::~Client()
{
	if (socket != nullptr)
	{
		socket->disconnect();
	}
	delete socket;
}

#ifdef _SERVER
void Client::Move(char x, char y)
{
	{
		chunkX += x;
		chunkY += y;

		for (int xx = 0; xx < x; xx++)
		{
			for (int xxx/*som yXD*/ = 0; xxx < 11; xxx++)
			{
				(short)((chunks[0])) >> 11;

			}
		}

		for (int xx = 0; xx > x; xx--)
		{
			for (int xxx/*som yXD*/ = 0; xxx < 11; xxx++)
			{
				(short)((chunks[0])) << 11;
			}

			for (int yyy = 0; yyy < 16; yyy++)
				chunks[y*11+xx] = 0;
		}
		/*for (int yy = 0; yy < y; yy++)
		{
			for (int xxx/*som yXD*//* = 0; xxx < 11; xxx++)
			{
				(short)(*(chunks[xxx])) >> 1;
				
			}
		}
		for (int yy = 0; yy > x; yy++)
		{
			for (int xxx/*som yXD*//* = 0; xxx < 11; xxx++)
			{
				(short)(*(chunks[x])) << 1;
				chunks[x][11] = 0;
			}
		}*/
	}
}
#endif