#include "Component.h"

Component::Component()
{
	_componentID = 0x80;
}

Component::~Component()
{
}

int Component::GetID()
{
	return _componentID;
}

void Component::SetObjectWorldPos(int worldPos)
{
    _objectWorldPos = worldPos;
}

int Component::GetObjectIWorldPos()
{
    return _objectWorldPos;
}
