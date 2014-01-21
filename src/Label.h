#ifdef CLIENT
#pragma once
#include <SFML/Graphics.hpp>
#include "Selectable.h"
#include "Selectable.h"

namespace gui
{
	class Label
		: public Selectable
	{
	private:
		int m_lineLength;
		int m_maxLength;
		sf::Text *m_text;
	public:
		Label(int x, int y, int width, int height, sf::String *text, sf::Font *font, int lineLength, int maxLength);
		~Label();
		virtual void Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight);
		void Clear() { m_text->setString(sf::String()); };
		sf::Text *getText() { return m_text; };
		void setText(sf::Text *text) { m_text = text; };
		void setLineLength(int lineLength) { m_lineLength = lineLength; };
		int getLineLength() { return m_lineLength; };
		void setMaxLength(int maxLength) { m_maxLength = maxLength; };
		int getMaxLength() { return m_maxLength; };
	};
}

#endif