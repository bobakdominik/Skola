#pragma once
#include "filter.h"
#include "criterion.h"

template<typename ObjectType, typename ValueType>
class FilterWithCriterion : public Filter<ObjectType>
{
public:
	
	~FilterWithCriterion();
	bool pass(ObjectType& object) override;

protected:
	FilterWithCriterion(Criterion<ObjectType, ValueType>* criterion);
	virtual bool passFilter(ValueType value) = 0;
protected:
	Criterion<ObjectType, ValueType>* criterion_;
};

template<typename ObjectType, typename ValueType>
inline FilterWithCriterion<ObjectType, ValueType>::FilterWithCriterion(Criterion<ObjectType, ValueType>* criterion):
	criterion_(criterion)
{
}

template<typename ObjectType, typename ValueType>
inline FilterWithCriterion<ObjectType, ValueType>::~FilterWithCriterion()
{
	delete this->criterion_;
	this->criterion_ = nullptr;
}

template<typename ObjectType, typename ValueType>
inline bool FilterWithCriterion<ObjectType, ValueType>::pass(ObjectType& object)
{
	return this->passFilter(this->criterion_->evaluate(object));
}
