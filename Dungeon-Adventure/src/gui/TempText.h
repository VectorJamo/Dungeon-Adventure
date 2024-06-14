#pragma once
#include "Label.h"

namespace gui {
	class TempText {
	private:
		static SDL_Renderer* _renderer;
		Label* _label;

	public:
		int maxAge, currentAge;

	public:
		TempText(int x, int y, const char* text, Font* font, int maxAge, SDL_Renderer* renderer);
		~TempText();

		void tick();
		void render();
	};
}

