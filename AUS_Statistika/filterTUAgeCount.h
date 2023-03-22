#pragma once
#include "filterWithInterval.h"
#include "criterionTUAgeCount.h"

class FilterTUAgeCount : public FilterWithInterval<TerritorialUnit*, int>
{
public:
	FilterTUAgeCount(Enums::GENDER gender, int age, int min, int max);
	void changeGender(Enums::GENDER newGender);
	void changeAge(int newAge);
	std::wstring toString() override;
private:
	Enums::GENDER gender_;
	int age_;
};
