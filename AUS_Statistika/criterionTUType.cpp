#include "criterionTUType.h"

CriterionTUType::CriterionTUType()
{
}

CriterionTUType::~CriterionTUType()
{
}

Enums::TERRITORIAL_UNIT_TYPE CriterionTUType::evaluate(TerritorialUnit*& unit)
{
	return unit->getTypeTU();
}