#pragma once

template<typename ObjectType, typename ResultType>
class Criterion
{
public:
	virtual ResultType evaluate(ObjectType& object) = 0;
	virtual ~Criterion();
private:

};

template<typename ObjectType, typename ResultType>
inline Criterion<ObjectType, ResultType>::~Criterion()
{
}
