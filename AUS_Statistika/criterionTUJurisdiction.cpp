#include "criterionTUJurisdiction.h"


CriterionTUJurisdiction::CriterionTUJurisdiction(TerritorialUnit* superiorTU) :
	tu_(superiorTU)
{
}

CriterionTUJurisdiction::~CriterionTUJurisdiction()
{
}

void CriterionTUJurisdiction::changeSuperiorTU(TerritorialUnit* newTU)
{
	this->tu_ = newTU;
}

bool CriterionTUJurisdiction::evaluate(TerritorialUnit*& unit)
{
	TerritorialUnit* superiorTU = &unit->getSuperiorTU();
	while (superiorTU != nullptr)
	{
		if (superiorTU == this->tu_)
		{
			return true;
		}
		superiorTU = &superiorTU->getSuperiorTU();
	}
	return false;
}