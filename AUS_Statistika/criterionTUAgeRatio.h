#pragma once
#include "criterionTU.h"
#include "criterionTUAgeCount.h"
#include "enums.h"

class CriterionTUAgeRatio : public CriterionTU<double>
{
public:
	CriterionTUAgeRatio(Enums::GENDER gender, int age);
	~CriterionTUAgeRatio();

	void changeGender(Enums::GENDER newGender);
	void changeAge(int newAge);
	double evaluate(TerritorialUnit*& unit) override;
private:
	Enums::GENDER gender_;
	int age_;
};
