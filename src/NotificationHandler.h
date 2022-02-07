#ifndef NOTIFICATIONHANDLER_H_
#define NOTIFICATIONHANDLER_H_

#include "Contract.h"
#include "ContractMember.h"
#include "EntitySystem.h"
#include "memoryManager.h"
#include <vector>
#include <map>

class Component;

class NotificationHandler {

public:

    NotificationHandler();
    ~NotificationHandler();

    ContractMember FindContractObserver(std::string contractName);
    ContractMember FindContractSender(std::string contractName);

    template<typename T>
    void PostContract(std::string contractName, T& paramOne)
    {
        Contracts::iterator it = _contracts.find(contractName);
        if (it != _contracts.end())
        {
            it->second->SetIsContractActive<T>(true);
            it->second->SetContractData<T>(paramOne);
            it->second->ExecuteEvent<T>();

            ContractMember* temp = it->second->GetContractSender();

            if (NULL != temp)
            {
                temp->SetContractSent(true);
            }
            safeDelete(temp);
        }
    }

    template<typename T>
    void JoinObserverToContract(ContractMember* observerObject,void (*f)(T& a), std::string contractName)
    {
        ContractObjects::iterator it = _contractObjects.find(contractName);
        if (it != _contractObjects.end())
        {
            Contract<T>* newContract = new Contract<T>();
            newContract->SetContractIndexID(contractIndexID);
            newContract->SetContractName(contractName);
            _contracts[contractName] = newContract;
            contractIndexID++;

            newContract->SetContractObserver(observerObject);
            newContract->SetEventFunction(f);
            newContract->DebugContractAddress();
            observerObject->SetCurrentContract(contractName);
            observerObject->SetContractID(it->second.ID);
        }
    }

    void CreateContract(std::string contractName);

    void JoinSenderToContract(ContractMember* senderObject, std::string contractName);

    void ProcessPostContracts();

private:
    typedef std::map<std::string, ContractMember> NotifiyObjects;
    typedef std::map<std::string, IContract*> Contracts;
    typedef std::map<std::string, ContractObject> ContractObjects;

    NotifiyObjects _objectsToNotify;
    NotifiyObjects _objectsToSend;

    Contracts _contracts;

    ContractObjects _contractObjects;

    std::vector<void(*)()> _eventsToProcessVoid;
    std::vector<void(*)(bool)> _eventsToProcessBool;
    std::vector<void(*)(int)> _eventsToProcessInt;
    std::vector<void(*)(float)> _eventsToProcessFloat;

    int contractIndexID;
    int contractProcessID;

    Contracts::iterator processContractIt;
};

#endif
