#pragma once
#include "filterWithInterval.h"
#include "criterionTUEducationRatio.h"

class FilterTUEducationRatio : public FilterWithInterval<TerritorialUnit*, double>
{
public:
	FilterTUEducationRatio(Enums::EDUCATION_TYPE educationType, double min, double max);
	std::wstring toString() override;
	void changeEducationType(Enums::EDUCATION_TYPE newEducationType);
private:
	Enums::EDUCATION_TYPE type_;
};

