#pragma once
#include "criterionTU.h"
#include "enums.h"

class CriterionTUAgeGroupCount : public CriterionTU<int>
{
public:
	CriterionTUAgeGroupCount(Enums::ECONOMIC_AGE_GROUP ageGroup);
	~CriterionTUAgeGroupCount();

	void changeAgeGroup(Enums::ECONOMIC_AGE_GROUP newAgeGroup);
	int evaluate(TerritorialUnit*& unit) override;
private:
	Enums::ECONOMIC_AGE_GROUP ageGroup_;
};
