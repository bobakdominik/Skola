#pragma once
#include "filterWithInterval.h"
#include "criterionTUAgeRatio.h"

class FilterTUAgeRatio : public FilterWithInterval<TerritorialUnit*, double>
{
public:
	FilterTUAgeRatio(Enums::GENDER gender, int age, double min, double max);
	void changeGender(Enums::GENDER newGender);
	void changeAge(int newAge);
	std::wstring toString() override;
private:
	Enums::GENDER gender_;
	int age_;
};
