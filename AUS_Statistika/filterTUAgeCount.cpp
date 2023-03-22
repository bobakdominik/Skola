#include "filterTUAgeCount.h"

FilterTUAgeCount::FilterTUAgeCount(Enums::GENDER gender, int age, int min, int max) :
	FilterWithInterval(new CriterionTUAgeCount(gender, age), min, max),
	gender_(gender),
	age_(age)
{
}

void FilterTUAgeCount::changeGender(Enums::GENDER newGender)
{
	this->gender_ = newGender;
	static_cast<CriterionTUAgeCount*>(this->criterion_)->changeGender(newGender);
}

void FilterTUAgeCount::changeAge(int newAge)
{
	this->age_ = newAge;
	static_cast<CriterionTUAgeCount*>(this->criterion_)->changeAge(newAge);
}

std::wstring FilterTUAgeCount::toString()
{
	return L"Filter UJVekPocet, Pohlavie: " + Enums::GENDERtoString(this->gender_) + L", Vek: " + std::to_wstring(this->age_)
		+ L", Minimum: " + std::to_wstring(this->min_) + L", Maximum: " + std::to_wstring(this->max_);
}