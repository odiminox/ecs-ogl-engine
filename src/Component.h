#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "EntityProcessing.h"

class Component
{
public:
	Component();
	~Component();

	int GetID();
    void SetObjectWorldPos(int worldPos);
    int GetObjectIWorldPos();
protected:
    int _componentID;

private:
    int _objectWorldPos;
};

#endif
