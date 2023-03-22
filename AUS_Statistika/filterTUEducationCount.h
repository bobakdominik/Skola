#pragma once
#include "filterWithInterval.h"
#include "criterionTUEducationCount.h"

class FilterTUEducationCount : public FilterWithInterval<TerritorialUnit*, int>
{
public:
	FilterTUEducationCount(Enums::EDUCATION_TYPE educationType, int min, int max);
	std::wstring toString() override;
	void changeEducationType(Enums::EDUCATION_TYPE newEducationType);
private:
	Enums::EDUCATION_TYPE educationType_;
};
