#include "criterionTUAgeCount.h"

CriterionTUAgeCount::CriterionTUAgeCount(Enums::GENDER gender, int age) :
	gender_(gender),
	age_(age)
{
}

CriterionTUAgeCount::~CriterionTUAgeCount()
{
}

void CriterionTUAgeCount::changeGender(Enums::GENDER newGender)
{
	this->gender_ = newGender;
}

void CriterionTUAgeCount::changeAge(int newAge)
{
	this->age_ = newAge;
}

int CriterionTUAgeCount::evaluate(TerritorialUnit*& unit)
{
	return unit->getAge().getAgeCount(this->gender_, this->age_);
}