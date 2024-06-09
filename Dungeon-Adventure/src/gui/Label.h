#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace gui {
	class Font {
	private:
		TTF_Font* _font;
		int _pointSize;

	public:
		Font(const char* filePath, int pointSize);
		~Font();

		inline TTF_Font* getFontInstance() { return _font; }
		inline int getPointSize() { return _pointSize; }
	};

	class Label {
	private:
		static SDL_Renderer* _renderer;

		int _x, _y, _width, _height;
		const char* _text;

		Font* _font;
		SDL_Color _color;
		SDL_Texture* _labelTexture;

	private:
		void createLabelTexture();

	public:
		Label(int x, int y, const char* text, Font* font, SDL_Renderer* renderer);
		~Label();
	
		void setPosition(int x, int y);
		void setFont(Font* font);
		void setTextColor(char r, char g, char b, char a);
		void setText(const char* text);

		void render();

		inline int getXPos() { return _x; }
		inline int getYPos() { return _y; }
		inline int getWidth() { return _width; }
		inline int getHeight() { return _height; }
		inline int getPointSize() { return _font->getPointSize(); }

	};

}
