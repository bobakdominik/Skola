#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "enums.h"
#include "structures/table/sorting/quick_sort.h"
#include "record.h"
#include "selectionCriterionMaxAgeGroup.h"
#include "selectionCriterionMinAgeGroup.h"
#include "criterionTUSuperior.h"
#include "filterTitle.h"
#include "filterTUAgeCount.h"
#include "filterTUAgeGroupCount.h"
#include "filterTUAgeGroupRatio.h"
#include "filterTUAgeRatio.h"
#include "filterTUEducationCount.h"
#include "filterTUEducationRatio.h"
#include "filterTUJurisdiction.h"
#include "filterTUType.h"
#include "compositeFilter.h"


class App
{
public:
	App(Record& record);
	~App();
	void run();


private:
	void runSearch();
	void runFilters();
	void runSorting();
	void runSelect();

	int readInt();
	int readInt(int min, int max);
	double readDouble();
	std::wstring readString();

	Enums::EDUCATION_TYPE chooseEducationType();
	Enums::ECONOMIC_AGE_GROUP chooseEconomicAgeGroup();
	Enums::TERRITORIAL_UNIT_TYPE chooseTUType(bool enableALL = true);
	Enums::GENDER chooseGender();
	TerritorialUnit* chooseTU();
	bool chooseAscending();
	int chooseAge();
	int chooseIntMin();
	int chooseIntMax();
	double chooseDoubleMin();
	double chooseDoubleMax();

	void printLine(std::string line);
	void printLine(std::wstring line);
	void printLine(int line);
	void printLine(double line);

	void pressEnter();
private:
	Record* record_;
	structures::UnsortedSequenceTable<std::wstring, TerritorialUnit*>* finalTable_;

	SelectionCriterionMaxAgeGroup* sCriterionMaxAgeGroup_;
	SelectionCriterionMinAgeGroup* sCriterionMinAgeGroup_;
	CriterionTUAgeCount* cAgeCount_;
	CriterionTUAgeGroupCount* cAgeGroupCount_;
	CriterionTUAgeGroupRatio* cAgeGroupRatio_;
	CriterionTUAgeRatio* cAgeRatio_;
	CriterionTUEducationCount* cEduCount_;
	CriterionTUEducationRatio* cEduRatio_;
	CriterionTUJurisdiction* cJurisdiction_;
	CriterionTUSuperior* cSuperior_;
	CriterionTUTitle* cTitle_;
	CriterionTUType* cType_;

	CompositeFilter<TerritorialUnit*>* compositeFilter_;
	FilterTitle* fTitle_;
	FilterTUType* fType_;
	FilterTUAgeCount* fAgeCount_;
	FilterTUAgeRatio* fAgeRatio_;
	FilterTUAgeGroupCount* fAgeGroupCount_;
	FilterTUAgeGroupRatio* fAgeGroupRatio_;
	FilterTUEducationCount* fEducationCount_;
	FilterTUEducationRatio* fEducationRatio_;
	FilterTUJurisdiction* fJurisdiction_;
};
