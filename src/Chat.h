#ifndef _SERVER
#pragma once
#include <vector>

namespace gui
{
	class Chat
	{
	private:
		std::vector<std::string> messages;
	public:
		Chat(void);
		~Chat(void);
	};
}
#endif

