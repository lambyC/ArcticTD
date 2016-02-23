#include "AnimatedObject.h"

using namespace std;

bool AnimatedObject::nextFrame(int speed)
{
	//determin if animation has come to the end of its loop
	//made for death animation.
	bool reachedEnd = false;

	if(_frame.left == _size.width * _maxFrames ){
		reachedEnd = true;
	}
	//Check if at either end of Animation
	if(_frame.left == _size.width * _maxFrames || _frame.left == 0){
		_isRight = _isRight ? false : true;
	}
	//move frame according to direction
	_frame.left += _isRight ? _size.width : - _size.width;
	//Check direction
	_frame.top = _size.height * (int)_frameRow;
	//update
	setTextureRect(_frame);
	//Add time
	_frameTime += 100;

	return reachedEnd;
}
