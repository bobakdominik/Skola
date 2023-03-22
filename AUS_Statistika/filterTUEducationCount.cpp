#include "filterTUEducationCount.h"

FilterTUEducationCount::FilterTUEducationCount(Enums::EDUCATION_TYPE educationType, int min, int max) :
	FilterWithInterval(new CriterionTUEducationCount(educationType), min, max),
	educationType_(educationType)
{
}

std::wstring FilterTUEducationCount::toString()
{
	return L"Filter UJVzdelaniePocet, Typ vzdelania: " + Enums::EDUCATION_TYPEtoString(this->educationType_)
		+ L", Minimum: " + std::to_wstring(this->min_) + L", Maximum: " + std::to_wstring(this->max_);
}

void FilterTUEducationCount::changeEducationType(Enums::EDUCATION_TYPE newEducationType)
{
	this->educationType_ = newEducationType;
	static_cast<CriterionTUEducationCount*>(this->criterion_)->changeEducationType(newEducationType);
}