
#include "NotificationHandler.h"
#include <cstddef>
#include <iostream>

NotificationHandler::NotificationHandler(){
    contractIndexID   = 0;
    contractProcessID = 0;
}
NotificationHandler::~NotificationHandler(){

}

void NotificationHandler::CreateContract(std::string contractName){

    ContractObject contract;
    contract.name = contractName;
    contract.ID = contractIndexID;
    _contractObjects[contractName] = contract;
}

void NotificationHandler::ProcessPostContracts(){
}

ContractMember NotificationHandler::FindContractObserver(std::string contractName){
    NotifiyObjects::iterator it = _objectsToNotify.find(contractName);
    if (it != _objectsToNotify.end())
    {
        return it->second;
    }
}

ContractMember NotificationHandler::FindContractSender(std::string contractName){
    NotifiyObjects::iterator it = _objectsToSend.find(contractName);
    if (it != _objectsToSend.end())
    {
        return it->second;
    }
}

void NotificationHandler::JoinSenderToContract(ContractMember* senderObject,std::string contractName){
    Contracts::iterator it = _contracts.find(contractName);
    if (it != _contracts.end())
    {
        printf("Contract sender is: %p\n", senderObject);
        it->second->SetContractSender(senderObject);
        senderObject->SetCurrentContract(contractName);
        senderObject->SetContractID(it->second->GetContractIndexID());
    }
}

