#pragma once
#include "criterionTU.h"
#include "enums.h"

class CriterionTUAgeCount : public CriterionTU<int>
{
public:
	CriterionTUAgeCount(Enums::GENDER gender, int age);
	~CriterionTUAgeCount();

	void changeGender(Enums::GENDER newGender);
	void changeAge(int newAge);
	int evaluate(TerritorialUnit*& unit) override;
private:
	Enums::GENDER gender_;
	int age_;
};