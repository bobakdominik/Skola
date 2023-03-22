#pragma once
#include "criterionTU.h"

class CriterionTUTitle: public CriterionTU<std::wstring>
{
public:
	CriterionTUTitle();
	~CriterionTUTitle();

	std::wstring evaluate(TerritorialUnit*& unit) override;
private:

};

