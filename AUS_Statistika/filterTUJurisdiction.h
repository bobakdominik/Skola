#pragma once
#include "filterWithValue.h"
#include "criterionTUJurisdiction.h"
#include "criterionTUTitle.h"

class FilterTUJurisdiction : public FilterWithValue<TerritorialUnit*, bool>
{
public:
	FilterTUJurisdiction(TerritorialUnit* superiorTU);
	void changeSuperiorTU(TerritorialUnit* newSuperiorTU);
	std::wstring toString() override;
private:
	TerritorialUnit* sTU_;
};
