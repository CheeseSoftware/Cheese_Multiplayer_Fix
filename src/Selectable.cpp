#ifdef MENUIDIOTI
#include "Selectable.h"

namespace gui
{
	Selectable::Selectable(std::function<GameState*(App&, GameState *gameState, const sf::Event)> onClickEvent)
	{
		this->onClickEvent = onClickEvent;
	}

	bool Selectable::getSelected()
	{
		return selected;
	}

	GameState *Selectable::EventUpdate(App& app, const sf::Event& event, GameState* gameState)
	{
		/*if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left && selected) // Selectable::EventUpdate should not call when OnLeftClick is called in any case.
			{
				Unselect();
			}
		}*/

		return nullptr;
	}

	void Selectable::OnLeftClick(App &app, GameState *gameState, const sf::Event &event)
	{
		selected = true;
		onClickEvent(app, gameState, event);
	}

	void Selectable::OnRightClick(App &app, GameState *gameState, const sf::Event &event)
	{
		selected = true;
	}

	void Selectable::Unselect()
	{
		selected = false;
	}
}
#endif