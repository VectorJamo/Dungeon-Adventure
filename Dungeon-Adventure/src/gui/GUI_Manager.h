#pragma once
#include "Button.h"
#include "TextField.h"
#include <vector>

namespace gui {
	class GUI_Manager {
	private:
		static std::vector<Button*> _buttons;
		static std::vector<TextField*> _textFields;

		static bool isShiftHold, isCapsOn;
	public:
		static int mouseX, mouseY;
		static void Update(SDL_Event& ev);

		static void AddButtonsToTrack(Button* button);
		static void AddTextFieldsToTrack(TextField* textField);
		static void ClearAll();
	};
}
