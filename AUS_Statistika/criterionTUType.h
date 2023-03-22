#pragma once
#include "criterionTU.h"
#include "enums.h"

class CriterionTUType : public CriterionTU<Enums::TERRITORIAL_UNIT_TYPE>
{
public:
	CriterionTUType();
	~CriterionTUType();

	Enums::TERRITORIAL_UNIT_TYPE evaluate(TerritorialUnit*& unit) override;
private:

};