#ifndef CONTACTPARAMETER_H_
#define CONTACTPARAMETER_H_

class Parameter
{
    public:
        virtual ~Parameter() {}
        template <class T> const T& Get() const;
        template <class T, class U> void SetValue(const U& rhs);
};


template<typename T>
class ContractParameter : public Parameter
{
    public:
        ContractParameter(const T& rhs) : value(rhs){}
        const T& Get() const {return value;}
        void SetValue(const T& rhs) {value = rhs;}
    private:
        T value;
};

template<typename T>
ContractParameter<T> CreateParameter(T& param) {
    ContractParameter<T> cparam(param);
    return cparam;
}

template<class T> const T& Parameter::Get() const { return dynamic_cast<const ContractParameter<T>&>(*this).Get(); }
template<class T, class U> void Parameter::SetValue(const U& rhs) { return dynamic_cast<ContractParameter<T>&>(*this).SetValue(rhs); }

#endif
