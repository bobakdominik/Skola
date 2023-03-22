#include "criterionTUAgeRatio.h"


CriterionTUAgeRatio::CriterionTUAgeRatio(Enums::GENDER gender, int age) :
	gender_(gender),
	age_(age)
{
}

CriterionTUAgeRatio::~CriterionTUAgeRatio()
{
}

void CriterionTUAgeRatio::changeGender(Enums::GENDER newGender)
{
	this->gender_ = newGender;
}

void CriterionTUAgeRatio::changeAge(int newAge)
{
	this->age_ = newAge;
}

double CriterionTUAgeRatio::evaluate(TerritorialUnit*& unit)
{
	return 100 * static_cast<double>(CriterionTUAgeCount(this->gender_, this->age_).evaluate(unit)) / static_cast<double>(unit->getNumberOfCitizens());
}