#include "criterionTUAgeGroupRatio.h"

CriterionTUAgeGroupRatio::CriterionTUAgeGroupRatio(Enums::ECONOMIC_AGE_GROUP ageGroup) :
	ageGroup_(ageGroup)
{
}

CriterionTUAgeGroupRatio::~CriterionTUAgeGroupRatio()
{
}


void CriterionTUAgeGroupRatio::changeAgeGroup(Enums::ECONOMIC_AGE_GROUP newAgeGroup)
{
	this->ageGroup_ = newAgeGroup;
}

double CriterionTUAgeGroupRatio::evaluate(TerritorialUnit*& unit)
{
	return 100 * static_cast<double>(CriterionTUAgeGroupCount(this->ageGroup_).evaluate(unit)) / static_cast<double>(unit->getNumberOfCitizens());
}