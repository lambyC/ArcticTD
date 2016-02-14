#ifndef GUARD_BUTTON_H
#define GUARD_BUTTON_H

#include "VisibleObject.h"

class Button : public VisibleObject
{
	public:
		Button();
		~Button();

		enum ButtonType {Drees, Erik, Emil, Felix = 3, Kros = 1, Jones = 2, Start = 0};
		Button(ButtonType type);

		void setButtonType(ButtonType type);
		void changeColour(sf::Color);

		ButtonType _action;
};

#endif
