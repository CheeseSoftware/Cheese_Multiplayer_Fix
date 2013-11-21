#pragma once

#define stringify ( name ) # name

enum MessageType
{
	NullMessage = 0,
	Init,
	RequestInit,
	Ping,
	Kick,
	WorldInit,
	CreatureInit,
	PlayerJoin,
	PlayerLeft,
	PlayerMove,
	ProjectileInit,
	EntityMove,
	EntityUpdate,
	BlockPlace,
	BlockMetadataChange
};