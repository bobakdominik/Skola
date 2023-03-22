#include "filterTUAgeRatio.h"

FilterTUAgeRatio::FilterTUAgeRatio(Enums::GENDER gender, int age, double min, double max) :
	FilterWithInterval(new CriterionTUAgeRatio(gender, age), min, max),
	gender_(gender),
	age_(age)
{
}

void FilterTUAgeRatio::changeGender(Enums::GENDER newGender)
{
	this->gender_ = newGender;
	static_cast<CriterionTUAgeRatio*>(this->criterion_)->changeGender(newGender);
}

void FilterTUAgeRatio::changeAge(int newAge)
{
	this->age_ = newAge;
	static_cast<CriterionTUAgeRatio*>(this->criterion_)->changeAge(newAge);
}

std::wstring FilterTUAgeRatio::toString()
{
	return L"Filter UJVekPodiel, Pohlavie: " + Enums::GENDERtoString(this->gender_) + L", Vek: " + std::to_wstring(this->age_)
		+ L", Minimum: " + std::to_wstring(this->min_) + L", Maximum: " + std::to_wstring(this->max_);
}