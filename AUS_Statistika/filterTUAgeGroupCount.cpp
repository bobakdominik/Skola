#include "filterTUAgeGroupCount.h"

FilterTUAgeGroupCount::FilterTUAgeGroupCount(Enums::ECONOMIC_AGE_GROUP ageGroup, int min, int max) :
	FilterWithInterval(new CriterionTUAgeGroupCount(ageGroup), min, max),
	ageGroup_(ageGroup)
{
}

void FilterTUAgeGroupCount::changeEconomicAgeGroup(Enums::ECONOMIC_AGE_GROUP newAgeGroup)
{
	this->ageGroup_ = newAgeGroup;
	static_cast<CriterionTUAgeGroupCount*>(this->criterion_)->changeAgeGroup(newAgeGroup);
}

std::wstring FilterTUAgeGroupCount::toString()
{
	return L"Filter UJVekovaSkupinaPocet, Vekova skupina: " + Enums::ECONOMIC_AGE_GROUPtoString(this->ageGroup_)
		+ L", Minimum: " + std::to_wstring(this->min_) + L", Maximum: " + std::to_wstring(this->max_);
}