#include "selectionCriterionMaxAgeGroup.h"

SelectionCriterionMaxAgeGroup::SelectionCriterionMaxAgeGroup(Enums::ECONOMIC_AGE_GROUP ageGroup) :
	SelectionCriterionMax(new CriterionTUAgeGroupCount(ageGroup))
{
}

void SelectionCriterionMaxAgeGroup::changeAgeGroup(Enums::ECONOMIC_AGE_GROUP newAgeGroup)
{
	static_cast<CriterionTUAgeGroupCount*>(this->criterion_)->changeAgeGroup(newAgeGroup);
}