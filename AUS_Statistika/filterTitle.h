#pragma once
#include "filterWithValue.h"
#include "territorialUnit.h"
#include "criterionTUTitle.h"

class FilterTitle : public FilterWithValue<TerritorialUnit*, std::wstring>
{
public:
	FilterTitle(std::wstring value);
	std::wstring toString() override;
private:
};
