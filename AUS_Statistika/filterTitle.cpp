#include "filterTitle.h"

FilterTitle::FilterTitle(std::wstring value) :
	FilterWithValue(new CriterionTUTitle(), value)
{
}

std::wstring FilterTitle::toString()
{
	return L"Filter UJNazov, nazov: " + this->value_;
}