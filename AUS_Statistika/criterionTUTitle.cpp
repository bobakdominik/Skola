#include "criterionTUTitle.h"

CriterionTUTitle::CriterionTUTitle()
{
}

CriterionTUTitle::~CriterionTUTitle()
{
}

std::wstring CriterionTUTitle::evaluate(TerritorialUnit*& unit)
{
	return unit->getOfficialTitle();
}