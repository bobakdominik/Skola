#include "criterionTUEducationCount.h"

CriterionTUEducationCount::CriterionTUEducationCount(Enums::EDUCATION_TYPE educationType) :
	educationType_(educationType)
{
}

CriterionTUEducationCount::~CriterionTUEducationCount()
{
}

void CriterionTUEducationCount::changeEducationType(Enums::EDUCATION_TYPE newEducationType)
{
	this->educationType_ = newEducationType;
}

int CriterionTUEducationCount::evaluate(TerritorialUnit*& unit)
{
	return unit->getEducation().getEducationCount(this->educationType_);
}