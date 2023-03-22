#pragma once
#include "criterionTU.h"
#include "enums.h"

class CriterionTUEducationCount : public CriterionTU<int>
{
public:
	CriterionTUEducationCount(Enums::EDUCATION_TYPE educationType);
	~CriterionTUEducationCount();

	void changeEducationType(Enums::EDUCATION_TYPE newEducationType);
	int evaluate(TerritorialUnit*& unit) override;
private:
	Enums::EDUCATION_TYPE educationType_;
};