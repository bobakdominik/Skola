#pragma once
#include "filterWithInterval.h"
#include "criterionTUAgeGroupRatio.h"

class FilterTUAgeGroupRatio : public FilterWithInterval<TerritorialUnit*, double>
{
public:
	FilterTUAgeGroupRatio(Enums::ECONOMIC_AGE_GROUP ageGroup, double min, double max);
	void changeEconomicAgeGroup(Enums::ECONOMIC_AGE_GROUP newAgeGroup);
	std::wstring toString() override;
private:
	Enums::ECONOMIC_AGE_GROUP ageGroup_;
};
