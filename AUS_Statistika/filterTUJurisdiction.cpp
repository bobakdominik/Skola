#include "filterTUJurisdiction.h"

FilterTUJurisdiction::FilterTUJurisdiction(TerritorialUnit* superiorTU) :
	FilterWithValue(new CriterionTUJurisdiction(superiorTU), true),
	sTU_(superiorTU)
{
}

void FilterTUJurisdiction::changeSuperiorTU(TerritorialUnit* newSuperiorTU)
{
	this->sTU_ = newSuperiorTU;
	static_cast<CriterionTUJurisdiction*>(this->criterion_)->changeSuperiorTU(newSuperiorTU);
}

std::wstring FilterTUJurisdiction::toString()
{
	return L"Filter UJPrislusnost, uzemna jednotka: " + CriterionTUTitle().evaluate(this->sTU_);
}