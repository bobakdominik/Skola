#include "filterTUType.h"

FilterTUType::FilterTUType(Enums::TERRITORIAL_UNIT_TYPE value) :
	FilterWithValue(new CriterionTUType(), value)
{
}

std::wstring FilterTUType::toString()
{
	return L"Filter UJTyp, typ: " + Enums::TERRITORIAL_UNIT_TYPEtoString(this->value_);
}