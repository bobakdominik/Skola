#include "criterionTUEducationRatio.h"

CriterionTUEducationRatio::CriterionTUEducationRatio(Enums::EDUCATION_TYPE educationType) :
	educationType_(educationType)
{
}

CriterionTUEducationRatio::~CriterionTUEducationRatio()
{
}

void CriterionTUEducationRatio::changeEducationType(Enums::EDUCATION_TYPE newEducationType)
{
	this->educationType_ = newEducationType;
}

double CriterionTUEducationRatio::evaluate(TerritorialUnit*& unit)
{
	return 100 * static_cast<double>(CriterionTUEducationCount(this->educationType_).evaluate(unit)) / static_cast<double>(unit->getNumberOfCitizens());
}