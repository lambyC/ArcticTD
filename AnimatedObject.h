#ifndef GUARD_ANIMATED_OBJECT_H
#define GUARD_ANIMATED_OBJECT_H

#include "VisibleObject.h"
#include "StdAfx.h"

class AnimatedObject : public VisibleObject
{
	public:
		enum FrameRow { First, Second, Third, Fourth };

		~AnimatedObject() {  };

		bool nextFrame(int speed);

		sf::Int32 getFrameTime() { return _frameTime; };

		int getFrameRow() { return (int)_frameRow; };
		int getMaxFrames() { return _maxFrames; };

		void setFrameTime(sf::Int32 t) { _frameTime = t; };

	protected:
		int _maxFrames;

		//frame direction
		//should be set to false to at start
		bool _isRight;

		//current frame and frame size
		sf::IntRect _frame;
		sf::IntRect _size;

		//speed loops through frame
		sf::Int32 _frameTime;

		FrameRow _frameRow;
};

#endif

