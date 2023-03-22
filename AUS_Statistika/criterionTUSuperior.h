#pragma once
#include "criterionTU.h"
#include "territorialUnit.h"

class CriterionTUSuperior : public CriterionTU<TerritorialUnit*>
{
public:
	CriterionTUSuperior();
	~CriterionTUSuperior();

	TerritorialUnit* evaluate(TerritorialUnit*& unit) override;
private:
};
