
#include "ContractMember.h"
#include "NotificationHandler.h"
#include "ContractParameter.h"
#include <stdio.h>
#include <iostream>

ContractMember::ContractMember()
{
    currentContract = "";
}

ContractMember::~ContractMember()
{
}

void ContractMember::SetContractSent(bool contractSent){
    this->contractSent = contractSent;
}
bool ContractMember::GetContractSent(){
    return this->contractSent;
}

void ContractMember::SetContractRecieved(bool contractRecieved){
    this->contractRecieved = contractRecieved;
}
bool ContractMember::GetContractRecieved(){
    return this->contractRecieved;
}

template<typename T>
void ContractMember::SetContractData(T& paramOne)
{
    ContractParameter<T> param(paramOne);
    params.push_back(&param);
    printf("Contract Parameter size: %zu\n", params.size());
}

std::vector<Parameter*> ContractMember::GetContractData()
{
    return params;
}
std::string ContractMember::GetCurrentContract()
{
    return currentContract;
}

void ContractMember::SetCurrentContract(std::string contractName)
{
    currentContract = contractName;
}

int ContractMember::GetContractID()
{
    return contractID;
}

void ContractMember::SetContractID(int contractID){
    this->contractID = contractID;
}

int ContractMember::GetContainerID(){
    return containerID;
}
void ContractMember::SetContainerID(int containerID){
    this->containerID = containerID;
}
