#ifndef NOTIFICATIONPAYLOADS_H_
#define NOTIFICATIONPAYLOADS_H_

#include <vector>
#include "TransformComponent.h"
#include "Object.h"

struct ObjectPayload {
    ObjectPayload(){
        com = new Component();
        object = new Object();
    }
    ~ObjectPayload(){}
    Object* object;
    Component* com;
};

#endif
