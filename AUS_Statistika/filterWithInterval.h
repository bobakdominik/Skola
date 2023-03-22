#pragma once
#include "criterion.h"
#include "filterWithCriterion.h"

template<typename ObjectType, typename ValueType>
class FilterWithInterval : public FilterWithCriterion<ObjectType, ValueType> {
public:
	FilterWithInterval(Criterion<ObjectType, ValueType>* criterion, ValueType min, ValueType max);
	void changeInterval(ValueType newMin, ValueType newMax);
protected:
	bool passFilter(ValueType value) override;
protected:
	ValueType min_;
	ValueType max_;
};

template<typename ObjectType, typename ValueType>
inline FilterWithInterval<ObjectType, ValueType>::FilterWithInterval(Criterion<ObjectType, ValueType>* criterion, ValueType min, ValueType max) :
	FilterWithCriterion<ObjectType, ValueType>(criterion),
	min_(min),
	max_(max)
{
}

template<typename ObjectType, typename ValueType>
inline void FilterWithInterval<ObjectType, ValueType>::changeInterval(ValueType newMin, ValueType newMax)
{
	this->min_ = newMin;
	this->max_ = newMax;
}

template<typename ObjectType, typename ValueType>
inline bool FilterWithInterval<ObjectType, ValueType>::passFilter(ValueType value)
{
	return value >= this->min_ && value <= this->max_;
}

