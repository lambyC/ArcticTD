#ifndef GUARD_BUTTON_H
#define GUARD_BUTTON_H

#include "VisibleObject.h"

class Button : public VisibleObject
{
	public:
		enum ButtonType {Drees, Erik, Emil, Felix = 3, Kros = 1, Jones = 2, Start = 0};

		Button();
		Button(ButtonType type);
		~Button();

		void setButtonType(ButtonType type);
		void changeColour(sf::Color);

		ButtonType getAction() { return _action; };

	protected:
		ButtonType _action;

};

#endif
