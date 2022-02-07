#pragma once

#include "ContractMember.h"
#include "NotificationPayloads.h"

class ComponentDelegate : public ContractMember
{
    public:
        ComponentDelegate();
        ~ComponentDelegate();
        static void BindComponentCallback(ObjectPayload& payload);
        static void DetachComponentCallback();

    private:
};
