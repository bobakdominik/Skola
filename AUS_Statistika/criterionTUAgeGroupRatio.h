#pragma once
#include "criterionTU.h"
#include "criterionTUAgeGroupCount.h"
#include "enums.h"

class CriterionTUAgeGroupRatio : public CriterionTU<double>
{
public:
	CriterionTUAgeGroupRatio(Enums::ECONOMIC_AGE_GROUP ageGroup);
	~CriterionTUAgeGroupRatio();

	void changeAgeGroup(Enums::ECONOMIC_AGE_GROUP newAgeGroup);
	double evaluate(TerritorialUnit*& unit) override;
private:
	Enums::ECONOMIC_AGE_GROUP ageGroup_;
};
