#pragma once
#include "Label.h"

namespace gui {
	class Button {
	private:
		static SDL_Renderer* _renderer;
		Label* _label;

		int _paddingX, _paddingY;
		char _r, _g, _b, _a;
		
		bool _hasOutline;
		int _outlineThickness;
		char _outlineR, _outlineG, _outlineB, _outlineA;

	public:
		bool isMouseOver;
		bool isClicked;

	public:
		Button(int x, int y, const char* text, Font* font, SDL_Renderer* renderer);
		~Button();

		// For button's label
		void setPosition(int x, int y);
		void setFont(Font* font);
		void setTextColor(char r, char g, char b, char a);

		// For button's outline
		void setOutlineColor(char r, char g, char b, char a);
		void setOutlineThickness(int thickness);

		// For the button
		void setColor(char r, char g, char b, char a);
		void setPaddingX(int paddingX);
		void setPaddingY(int paddingY);

		void update(SDL_Event& ev);
		void render();

		inline int getXPos() { return _label->getXPos() - _paddingX; }
		inline int getYPos() { return _label->getYPos() - _paddingY; }
		inline int getWidth() { return _label->getWidth() + 2*_paddingX; }
		inline int getHeight() { return _label->getHeight() + 2*_paddingY; }
	};
}
