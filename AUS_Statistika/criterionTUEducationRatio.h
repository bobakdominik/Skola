#pragma once
#include "criterionTU.h"
#include "criterionTUEducationCount.h"
#include "enums.h"

class CriterionTUEducationRatio : public CriterionTU<double>
{
public:
	CriterionTUEducationRatio(Enums::EDUCATION_TYPE educationType);
	~CriterionTUEducationRatio();

	void changeEducationType(Enums::EDUCATION_TYPE newEducationType);
	double evaluate(TerritorialUnit*& unit) override;
private:
	Enums::EDUCATION_TYPE educationType_;
};