#pragma once
#include "filterWithValue.h"
#include "territorialUnit.h"
#include "enums.h"
#include "criterionTUType.h"

class FilterTUType : public FilterWithValue<TerritorialUnit*, Enums::TERRITORIAL_UNIT_TYPE>
{
public:
	FilterTUType(Enums::TERRITORIAL_UNIT_TYPE value);
	std::wstring toString() override;

private:
};
