#ifdef MENUIDIOTI
#include "Selectable.h"
#include "GameState.h"

namespace gui
{
	Selectable::Selectable(/*ClickEvent leftClickEvent, ClickEvent rightClickEvent*/)
	{
		//onLeftClickEvent = leftClickEvent;
		//onRightClickEvent = rightClickEvent;
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

		return gameState;
	}

	void Selectable::Draw(App &app, float x, float y)
	{

	}

	void Selectable::OnLeftClick(App &app, const sf::Event &event, GameState *gameState)
	{
		selected = true;
		//onLeftClickEvent(app, event, gameState);
	}

	void Selectable::OnRightClick(App &app, const sf::Event &event, GameState *gameState)
	{
		selected = true;
		//onRightClickEvent(app, event, gameState);
	}

	void Selectable::Unselect()
	{
		selected = false;
	}
}
#endif