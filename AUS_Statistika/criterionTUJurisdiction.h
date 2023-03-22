#pragma once
#include "criterionTU.h"

class CriterionTUJurisdiction : public CriterionTU<bool>
{
public:
	CriterionTUJurisdiction(TerritorialUnit* superiorTU);
	~CriterionTUJurisdiction();

	void changeSuperiorTU(TerritorialUnit* newTU);
	bool evaluate(TerritorialUnit*& unit) override;
private:
	TerritorialUnit* tu_;
};
