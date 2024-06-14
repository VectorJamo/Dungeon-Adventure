#pragma once
#include "Button.h"
#include "Label.h"
#include "TextField.h"
#include "TempText.h"
#include <vector>

namespace gui {
	class GUI_Manager {
	private:
		static std::vector<Button*> _buttons;
		static std::vector<TextField*> _textFields;
		static std::vector<TempText*> _activeTempTexts;

		static bool isShiftHold, isCapsOn;

	public:
		static int mouseX, mouseY;
		static void Update(SDL_Event& ev);

		static void AddButtonsToTrack(Button* button);
		static void AddTextFieldsToTrack(TextField* textField);
		static void ClearAll();

		static void AddTempText(int x, int y, const char* text, Font* font, int maxAge, SDL_Renderer* renderer);

		static void UpdateTempTexts();
		static void RenderTempTexts();
	};
}
