#pragma once

#include <string>
#include <vector>
#include "ContractParameter.h"

class ContractMember {

    friend class NotificationHandler;

public:
    ContractMember();
    ~ContractMember();

    std::string GetCurrentContract();
    void SetCurrentContract(std::string contractName);
    int GetContractID();
    void SetContractID(int contractID);
    int GetContainerID();
    void SetContainerID(int containerID);
    std::vector<Parameter*> GetContractData();

protected:
    void SetContractSent(bool contractSent);
    bool GetContractSent();

    void SetContractRecieved(bool contractRecieved);
    bool GetContractRecieved();

    template<typename T>
    void SetContractData(T& paramOne);

private:
    std::string currentContract;
    int contractID;
    int containerID;
    bool contractSent;
    bool contractRecieved;
    std::vector<Parameter*> params;
};
