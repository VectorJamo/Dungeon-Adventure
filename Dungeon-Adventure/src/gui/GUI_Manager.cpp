#include "GUI_Manager.h"
#include <iostream>

std::vector<gui::Button*> gui::GUI_Manager::_buttons;
std::vector<gui::TextField*> gui::GUI_Manager::_textFields;
int gui::GUI_Manager::mouseX;
int gui::GUI_Manager::mouseY;
bool gui::GUI_Manager::isShiftHold = false;
bool gui::GUI_Manager::isCapsOn = false;
void gui::GUI_Manager::AddButtonsToTrack(Button* button) {
	_buttons.push_back(button);
}

void gui::GUI_Manager::AddTextFieldsToTrack(TextField* textField) {
	_textFields.push_back(textField);
}

void gui::GUI_Manager::ClearAllButtons() {
	_buttons.clear();
}

void gui::GUI_Manager::Update(SDL_Event& ev) {
	SDL_GetMouseState(&mouseX, &mouseY);

	// Buttons
	// Check if the mouse is inside any of the buttons
	for (auto& button : _buttons) {
		if (mouseX > button->getXPos() && mouseX < button->getXPos() + button->getWidth() &&
			mouseY > button->getYPos() && mouseY < button->getYPos() + button->getHeight()) {
			button->isMouseOver = true;
		}
		else {
			button->isMouseOver = false;
		}
	}

	if (ev.type == SDL_MOUSEBUTTONDOWN) {
		if (ev.button.button == SDL_BUTTON_LEFT) {
			for (auto& button : _buttons) {
				if (button->isMouseOver) {
					button->isClicked = true;
				}
			}
		}
	}

	// Text Fields
	for (auto& textField : _textFields) {
		if (mouseX > textField->getXPos() && mouseX < textField->getXPos() + textField->getWidth() &&
			mouseY > textField->getYPos() && mouseY < textField->getYPos() + textField->getHeight()) {
			textField->isMouseOver = true;
		}
		else {
			textField->isMouseOver = false;
		}
	}

	if (ev.type == SDL_MOUSEBUTTONDOWN) {
		if (ev.button.button == SDL_BUTTON_LEFT) {
			for (auto& textField : _textFields) {
				if (textField->isMouseOver) {
					textField->onFocus = true;
				}
				else {
					textField->onFocus = false;
				}
			}
		}
	}

	if (ev.type == SDL_KEYDOWN) {
		if (ev.key.keysym.sym == SDLK_CAPSLOCK) {
			if (isCapsOn)
				isCapsOn = false;
			else
				isCapsOn = true;
		}
		else if (ev.key.keysym.sym == SDLK_LSHIFT) {
			isShiftHold = true;
		}
		for (auto& textField : _textFields) {
			if (textField->onFocus) {
				// First, check if the typed key is a backspace key
				if (ev.key.keysym.sym == SDLK_BACKSPACE) {
					if (textField->getCurrentText().size() > 1) {
						textField->getCurrentText().pop_back();
						std::string result = textField->getCurrentText();
						textField->setText(result);
					}
					else {
						textField->setText(" ");
					}
				}
				else if (textField->getWidth() > textField->getLabelWidth() + textField->getLabelPointSize() 
					&& ((ev.key.keysym.sym == 32) || (ev.key.keysym.sym >= 97 && ev.key.keysym.sym <= 122) || (ev.key.keysym.sym >= 48 && ev.key.keysym.sym <= 57))) {
					// Then allow to insert text inside the text field as long as it does not overflow
					char key = (char)ev.key.keysym.sym;
					if (isCapsOn || isShiftHold) {
						key = key - 32;
					}
					std::string newText = textField->getCurrentText() + key;
					std::cout << newText << std::endl;
					textField->setText(newText);
				}				
			}
		}
	}
	if (ev.type == SDL_KEYUP) {
		if (ev.key.keysym.sym == SDLK_LSHIFT) {
			isShiftHold = false;
		}
	}

}