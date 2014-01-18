#ifndef _SERVER
#pragma once
#include "Label.h"
<<<<<<< HEAD
typedef std::function<GameState*(App& app, const sf::Event& event, GameUtility* gameUtility, float x, float y)> ClickFunction;
=======
typedef std::function<void(App& app, const sf::Event& event, GameState* gameState, float x, float y)> ClickFunction;
>>>>>>> c953a28c2ff85939864a8166e4b9475db0da2b73
namespace gui
{
	class Button : public Label
	{
	private:
		ClickFunction onLeftClickFunction;
		ClickFunction onRightClickFunction;
	public:
		Button(int x, int y, int width, int height, sf::String *text, sf::Font *font, int lineLength, int maxLength, ClickFunction leftClick, ClickFunction rightClick);
		~Button(void);
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameUtility* gameUtility, float x, float y);
		virtual void Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight);
		virtual void OnLeftClick(App &app, const sf::Event &event, GameUtility* gameUtility, float x, float y);
		virtual void OnRightClick(App &app, const sf::Event &event, GameUtility* gameUtility, float x, float y);
	};
}
#endif

