#pragma once
#include "filterWithInterval.h"
#include "criterionTUAgeGroupCount.h"

class FilterTUAgeGroupCount : public FilterWithInterval<TerritorialUnit*, int>
{
public:
	FilterTUAgeGroupCount(Enums::ECONOMIC_AGE_GROUP ageGroup, int min, int max);
	void changeEconomicAgeGroup(Enums::ECONOMIC_AGE_GROUP newAgeGroup);
	std::wstring toString() override;
private:
	Enums::ECONOMIC_AGE_GROUP ageGroup_;
};
