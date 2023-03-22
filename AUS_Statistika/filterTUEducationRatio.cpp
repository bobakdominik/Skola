#include "filterTUEducationRatio.h"

FilterTUEducationRatio::FilterTUEducationRatio(Enums::EDUCATION_TYPE educationType, double min, double max) :
	FilterWithInterval(new CriterionTUEducationRatio(educationType), min, max),
	type_(educationType)
{
}

std::wstring FilterTUEducationRatio::toString()
{
	return L"Filter UJVzdelaniePodiel, Typ vzdelania: " + Enums::EDUCATION_TYPEtoString(this->type_)
		+ L", Minimum: " + std::to_wstring(this->min_) + L", Maximum: " + std::to_wstring(this->max_);
}

void FilterTUEducationRatio::changeEducationType(Enums::EDUCATION_TYPE newEducationType)
{
	this->type_ = newEducationType;
	static_cast<CriterionTUEducationRatio*>(this->criterion_)->changeEducationType(newEducationType);
}