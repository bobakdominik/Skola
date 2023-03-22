#include "filterTUAgeGroupRatio.h"

FilterTUAgeGroupRatio::FilterTUAgeGroupRatio(Enums::ECONOMIC_AGE_GROUP ageGroup, double min, double max) :
	FilterWithInterval(new CriterionTUAgeGroupRatio(ageGroup), min, max),
	ageGroup_(ageGroup)
{
}

void FilterTUAgeGroupRatio::changeEconomicAgeGroup(Enums::ECONOMIC_AGE_GROUP newAgeGroup)
{
	this->ageGroup_ = newAgeGroup;
	static_cast<CriterionTUAgeGroupRatio*>(this->criterion_)->changeAgeGroup(newAgeGroup);
}

std::wstring FilterTUAgeGroupRatio::toString()
{
	return L"Filter UJVekovaSkupinaPodiel, Vekova skupina: " + Enums::ECONOMIC_AGE_GROUPtoString(this->ageGroup_)
		+ L", Minimum: " + std::to_wstring(this->min_) + L", Maximum: " + std::to_wstring(this->max_);
}