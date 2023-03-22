#pragma once
#include "filter.h"
#include "structures/list/array_list.h"

template<typename ObjectType>
class CompositeFilter : public Filter<ObjectType>
{
public:
	CompositeFilter();
	~CompositeFilter();

	void registerFilter(Filter<ObjectType>* filter);
	bool pass(ObjectType& object) override;
	void clear();

	std::wstring toString() override;

private:
	structures::ArrayList<Filter<ObjectType>*>* filters_;
};



template<typename ObjectType>
inline CompositeFilter<ObjectType>::CompositeFilter():
	filters_(new structures::ArrayList<Filter<ObjectType>*>())
{
}

template<typename ObjectType>
inline CompositeFilter<ObjectType>::~CompositeFilter()
{
	delete this->filters_;
	this->filters_ = nullptr;
}

template<typename ObjectType>
inline void CompositeFilter<ObjectType>::registerFilter(Filter<ObjectType>* filter)
{
	for (Filter<ObjectType>* f: *this->filters_)
	{
		if (f == filter)
		{
			return;
		}
	}
	this->filters_->add(filter);
}

template<typename ObjectType>
inline bool CompositeFilter<ObjectType>::pass(ObjectType& object)
{
	for (Filter<ObjectType>* filter: *this->filters_)
	{
		if (!filter->pass(object))
		{
			return false;
		}
	}
	return true;
}

template<typename ObjectType>
inline void CompositeFilter<ObjectType>::clear()
{
	this->filters_->clear();
}

template<typename ObjectType>
inline std::wstring CompositeFilter<ObjectType>::toString()
{
	std::wstring str = L"Registrovane filtre:\n";
	for (Filter<ObjectType>* f : *this->filters_)
	{
		str += f->toString() + L"\n";
	}

	return str;
}
