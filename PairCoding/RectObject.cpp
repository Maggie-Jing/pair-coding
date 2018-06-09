#include "RectObject.h"

RectObject::RectObject()
{
}

RectObject::~RectObject()
{
}

void RectObject::_setLife() {
	life = child_life;
}
void RectObject::_setChildLife(bool my_life) {
	child_life = my_life;
}


