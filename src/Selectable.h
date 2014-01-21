#ifdef CLIENT
#pragma once
#include <functional>
#include "IMenuItem.h"
#include "App.h"
#include "PositionType.h"

#define CALLBACKFUNCTION__on(name) gui::ClickFunction on##name; public: void setOn##name##Callback(gui::ClickFunction function) { on##name = function; } protected:

namespace gui
{
	typedef std::function<void(App& app, const sf::Event& event, float x, float y)> ClickFunction;

	class Selectable : public virtual IMenuItem
	{
	protected:
		bool selected;
		bool down;
		bool clicked;

		int m_x;
		int m_y;
		int m_width;
		int m_height;
		int m_widthOffset;
		int m_heightOffset;
		
		CALLBACKFUNCTION__on(LMBPressedFunction)
		CALLBACKFUNCTION__on(LMBReleasedFunction)
		CALLBACKFUNCTION__on(LMBClickFunction)
		CALLBACKFUNCTION__on(RMBPressedFunction)
		CALLBACKFUNCTION__on(RMBReleasedFunction)
		CALLBACKFUNCTION__on(RMBClickFunction)
		CALLBACKFUNCTION__on(HoverFunction)
		CALLBACKFUNCTION__on(HoverReleasedFunction)

		sf::Sprite *m_texture;
		PositionType m_positionType;
		Selectable(int x, int y, int width, int height);
	public:
		virtual bool getSelected();
		virtual GameState *EventUpdate(App& app, const sf::Event& event, float x, float y);
		virtual GameState *Update(App &app, Game &game);
		virtual void Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)=0;

		virtual void OnLMBPressed(	App &app, const sf::Event &event, float x, float y);
		virtual void OnLMBReleased(	App &app, const sf::Event &event, float x, float y);
		virtual void OnLMBClick(	App &app, const sf::Event &event, float x, float y);
		virtual void OnRMBPressed(	App &app, const sf::Event &event, float x, float y);
		virtual void OnRMBReleased(	App &app, const sf::Event &event, float x, float y);
		virtual void OnRMBClick(	App &app, const sf::Event &event, float x, float y);

		virtual void OnHover(App &app, const sf::Event &event, float x, float y);
		virtual void OnHoverReleased(App &app, const sf::Event &event, float x, float y);
		sf::Vector2f getPosition() { return sf::Vector2f(m_x, m_y); }
		virtual sf::Vector2f getSize();
		virtual sf::Vector2f Selectable::getPositionOffset(float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight);
		void setPositionType(PositionType positionType);
		void setTexture(sf::Sprite *texture) { m_texture = texture; };
		void Unselect();
	};
}
#endif