#include "criterionTUSuperior.h"

CriterionTUSuperior::CriterionTUSuperior()
{
}

CriterionTUSuperior::~CriterionTUSuperior()
{
}

TerritorialUnit* CriterionTUSuperior::evaluate(TerritorialUnit*& unit)
{
	return &unit->getSuperiorTU();
}