#include "criterionTUAgeGroupCount.h"


CriterionTUAgeGroupCount::CriterionTUAgeGroupCount(Enums::ECONOMIC_AGE_GROUP ageGroup) :
	ageGroup_(ageGroup)
{
}

CriterionTUAgeGroupCount::~CriterionTUAgeGroupCount()
{
}


void CriterionTUAgeGroupCount::changeAgeGroup(Enums::ECONOMIC_AGE_GROUP newAgeGroup)
{
	this->ageGroup_ = newAgeGroup;
}

int CriterionTUAgeGroupCount::evaluate(TerritorialUnit*& unit)
{
	return unit->getAge().getEconomicAgeCount(Enums::GENDER::UNSPECIFIED_GENDER, this->ageGroup_);
}