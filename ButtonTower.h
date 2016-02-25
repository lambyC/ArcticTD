#ifndef GUARD_BUTTON_TOWER_H
#define GUARD_BUTTON_TOWER_H

#include "StdAfx.h"
#include "Button.h"

class ButtonTower : public Button
{
	public:
		ButtonTower(ButtonType BT, int cost) : _cost(cost) { _action = BT; } ;
		~ButtonTower() {  };

		void setCost(int cost) { _cost = cost; };
		int getCost() { return _cost; }

	private:
		int _cost;
};

#endif
