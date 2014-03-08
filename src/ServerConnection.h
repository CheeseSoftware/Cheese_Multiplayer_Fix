#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>
#include <queue>
class Client;
class World;



class ServerConnection
{
public:
	ServerConnection(int port, World *world);
	~ServerConnection(void);
	void Broadcast(sf::Packet packet);
	void KickClient(int ID, std::string reason);
	virtual void Update();

	sf::Mutex lockObject;
	std::queue<std::pair<sf::Packet*, Client*>> packets;
	std::map<int, std::string> toKick;
	std::map<int, Client*> clients;
private:
	void PingClients();
	void AcceptReceive();
	sf::Thread *acceptReceiveThread;
	int GetFreeClientId();
	sf::IpAddress localIP;
	sf::IpAddress publicIP;
	sf::Clock pingTimeout;
	sf::TcpListener s;
	sf::SocketSelector selector;
	World* currentWorld;
};