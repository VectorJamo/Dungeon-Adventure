#pragma once
#include "Label.h"
#include <string>

namespace gui {
	class TextField {
	private:
		static SDL_Renderer* _renderer;
		Label* _label;
		std::string _text;
		int _numCharacters;

		int _width, _height;
		char _r, _g, _b, _a;

	public:
		bool isMouseOver;
		bool onFocus; // 'true' if the user clicks on the textfield
	
	public:
		TextField(int x, int y, int width, int height, Font* font, SDL_Renderer* renderer);
		~TextField();

		void setPosition(int x, int y);
		void setFont(Font* font);
		void setColor(char r, char g, char b, char a);
		void setTextColor(char r, char g, char b, char a);

		void render();
		void setText(const std::string& text);

		inline int getXPos() { return _label->getXPos(); }
		inline int getYPos() { return _label->getYPos(); }
		inline int getWidth() { return _width; }
		inline int getHeight() { return _height; }
		inline int getLabelWidth() { return _label->getWidth(); }
		inline int getLabelPointSize() { return _label->getPointSize(); }

		inline std::string& getCurrentText() { return _text; }
	};
}
