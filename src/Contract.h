#pragma once

#include "ContractMember.h"
#include <cstdio>

struct ContractObject
{
    public:
        std::string name;
        int ID;
        ContractMember* observer;
        ContractMember* sender;
};

template<typename T>
struct EventCallback
{
    void (*_eventFunction)(T& p);
    T* param;
};

class IContract {
public:
    virtual ~IContract(){}
    std::string GetContractName(){}
    void SetContractName(std::string contractName){}

    int GetContractIndexID(){}
    void SetContractIndexID(int contractIndexID){}

    int GetContractProrcessID(){}
    void SetContractProcessID(int contractProcessID){}

    ContractMember* GetContractObserver(){}
    void SetContractObserver(ContractMember* observer){}

    ContractMember* GetContractSender(){}
    void SetContractSender(ContractMember* sender){}

    void DebugContractAddress(){}

    template <class T> bool GetIsContractActive();
    template <class T> void SetIsContractActive(bool isActive);

    template <class T> void ExecuteEvent();

    template <class T, class U> void SetContractData(U& Param);
    template <class T, class U> void SetEventFunction(void (*eventFunction)(U& p));

    void DestoryContract(){}
};

template<typename T>
class Contract : public IContract{

public:

    typedef EventCallback<T> CallbackObject;
    friend class NotificationHandler;

    Contract(){
        _isActivated = false;
        _remove = false;
        _observer = NULL;
        _sender = NULL;
    }
    ~Contract(){

    }

    std::string GetContractName(){
        return _contractName;
    }
    void SetContractName(std::string contractName){
        contractName = contractName;
    }

    int GetContractIndexID(){
        return _contractIndexID;
    }
    void SetContractIndexID(int contractIndexID){
        _contractIndexID = contractIndexID;
    }

    int GetContractProrcessID(){
        return _contractProcessID;
    }
    void SetContractProcessID(int contractProcessID){
        _contractProcessID = contractProcessID;
    }

    ContractMember* GetContractObserver(){
        return _observer;
    }
    void SetContractObserver(ContractMember* observer){
        _observer = observer;
    }

    ContractMember* GetContractSender(){
        return _sender;
    }
    void SetContractSender(ContractMember* sender){
        _sender = sender;
    }

    void SetContractData(T& Param)
    {
        _eventCallback.param = &Param;
    }

    void SetEventFunction(void (*eventFunction)(T& p)){
        _eventCallback._eventFunction = eventFunction;
    }

    bool GetIsContractActive(){
        return _isActivated;
    }
    void SetIsContractActive(bool isActive){
        _isActivated = isActive;
    }

    void DestoryContract(){
        _remove = true;

    }
    void ExecuteEvent(){
        (*_eventCallback._eventFunction)(*_eventCallback.param);
    }

    void DebugContractAddress(){
        printf("Callback address is: %p\n", &_eventCallback._eventFunction);
    }

private:

    ContractMember* _observer;
    ContractMember* _sender;

    int _contractIndexID;
    int _contractProcessID;
    std::string _contractName;

    bool _isActivated;
    bool _remove;


    CallbackObject _eventCallback;
};
template<class T> void IContract::ExecuteEvent() {return static_cast<Contract<T>&>(*this).ExecuteEvent();}

template<class T> void IContract::SetIsContractActive(bool isActive) {return static_cast<Contract<T>&>(*this).SetIsContractActive(isActive); }
template<class T> bool IContract::GetIsContractActive() { return static_cast<Contract<T>&>(*this).GetIsContractActive();}

template<class T, class U> void IContract::SetContractData(U& rhs) { return static_cast<Contract<T>&>(*this).SetContractData(rhs); }
template<class T, class U> void IContract::SetEventFunction(void (*eventfunction)(U& rhs)) { return static_cast<Contract<T>&>(*this).SetEventFunction(eventfunction); }


