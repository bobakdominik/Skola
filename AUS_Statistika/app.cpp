#include "app.h"

App::App(Record& record) :
	record_(&record),
	finalTable_(new structures::UnsortedSequenceTable<std::wstring, TerritorialUnit*>()),
	sCriterionMaxAgeGroup_(new SelectionCriterionMaxAgeGroup(Enums::PRODUCTIVE)),
	sCriterionMinAgeGroup_(new SelectionCriterionMinAgeGroup(Enums::PRODUCTIVE)),
	cAgeCount_(new CriterionTUAgeCount(Enums::UNSPECIFIED_GENDER,0)),
	cAgeGroupCount_(new CriterionTUAgeGroupCount(Enums::UNSPECIFIED)),
	cAgeGroupRatio_(new CriterionTUAgeGroupRatio(Enums::UNSPECIFIED)),
	cAgeRatio_(new CriterionTUAgeRatio(Enums::UNSPECIFIED_GENDER, 0)),
	cEduCount_(new CriterionTUEducationCount(Enums::UNKNOWN)),
	cEduRatio_(new CriterionTUEducationRatio(Enums::UNKNOWN)),
	cJurisdiction_(new CriterionTUJurisdiction(nullptr)),
	cSuperior_(new CriterionTUSuperior()),
	cTitle_(new CriterionTUTitle()),
	cType_(new CriterionTUType()),
	compositeFilter_(new CompositeFilter<TerritorialUnit*>()),
	fTitle_(new FilterTitle(L"")),
	fType_(new FilterTUType(Enums::ALL)),
	fAgeCount_(new FilterTUAgeCount(Enums::UNSPECIFIED_GENDER, 0, 0, 100)),
	fAgeRatio_(new FilterTUAgeRatio(Enums::UNSPECIFIED_GENDER, 0, 0, 100)),
	fAgeGroupCount_(new FilterTUAgeGroupCount(Enums::PRODUCTIVE, 0, 100)),
	fAgeGroupRatio_(new FilterTUAgeGroupRatio(Enums::PRODUCTIVE, 0, 100)),
	fEducationCount_(new FilterTUEducationCount(Enums::UNKNOWN, 0, 100)),
	fEducationRatio_(new FilterTUEducationRatio(Enums::UNKNOWN, 0, 100)),
	fJurisdiction_(new FilterTUJurisdiction(nullptr))
{
}

App::~App()
{
	delete this->finalTable_;

	delete this->sCriterionMaxAgeGroup_;
	delete this->sCriterionMinAgeGroup_;
	delete this->cAgeCount_;
	delete this->cAgeGroupCount_;
	delete this->cAgeGroupRatio_;
	delete this->cAgeRatio_;
	delete this->cEduCount_;
	delete this->cEduRatio_;
	delete this->cJurisdiction_;
	delete this->cSuperior_;
	delete this->cTitle_;
	delete this->cType_;

	delete this->compositeFilter_;
	delete this->fTitle_;
	delete this->fType_;
	delete this->fAgeCount_;
	delete this->fAgeRatio_;
	delete this->fAgeGroupCount_;
	delete this->fAgeGroupRatio_;
	delete this->fEducationCount_;
	delete this->fEducationRatio_;
	delete this->fJurisdiction_;

	this->finalTable_ = nullptr;
	this->record_ = nullptr;

	this->sCriterionMaxAgeGroup_ = nullptr;
	this->sCriterionMinAgeGroup_ = nullptr;
	this->cAgeCount_ = nullptr;
	this->cAgeGroupCount_ = nullptr;
	this->cAgeGroupRatio_ = nullptr;
	this->cAgeRatio_ = nullptr;
	this->cEduCount_ = nullptr;
	this->cEduRatio_ = nullptr;
	this->cJurisdiction_ = nullptr;
	this->cSuperior_ = nullptr;
	this->cTitle_ = nullptr;
	this->cType_ = nullptr;

	this->compositeFilter_ = nullptr;
	this->fTitle_ = nullptr;
	this->fType_ = nullptr;
	this->fAgeCount_ = nullptr;
	this->fAgeRatio_ = nullptr;
	this->fAgeGroupCount_ = nullptr;
	this->fAgeGroupRatio_ = nullptr;
	this->fEducationCount_ = nullptr;
	this->fEducationRatio_ = nullptr;
	this->fJurisdiction_ = nullptr;
}

void App::run()
{
	int input = 0;
	printLine("###################################################################\n");
	printLine("Spracovanie udajov zo Scitania obyvatelov domov a bytov z roku 2021\n");
	printLine("###################################################################\n\n");
	do
	{
		printLine("\nZadajte cislo akcie:\n");
		printLine("1. Bodove vyhladavanie\n");
		printLine("2. Filtrovanie\n");
		printLine("3. Triedenie\n" );
		printLine("4. Vyber najlepsich\n");
		printLine("0. Koniec\n");
		input = this->readInt();
		switch (input)
		{
		case 0:
			break;
		case 1:
			this->runSearch();
			break;
		case 2:
			this->runFilters();
			break;
		case 3:
			this->runSorting();
			break;
		case 4:
			this->runSelect();
			break;
		default:
			printLine("Nespravny vyber\n\n");
			break;
		}

	} while (input != 0);

	printLine("---- Koniec ----\n");
}

void App::runSearch()
{
	printLine("\n--- Bodove vyhladavanie ---\n");

	TerritorialUnit* tu = this->chooseTU();
	Enums::EDUCATION_TYPE educationType = this->chooseEducationType();
	Enums::ECONOMIC_AGE_GROUP ageGroupType = this->chooseEconomicAgeGroup();

	this->cEduCount_->changeEducationType(educationType);
	this->cAgeGroupCount_->changeAgeGroup(ageGroupType);

	printLine("Zvolena uzemna jednotka:\n");
	printLine("Nazov: ");
	printLine(this->cTitle_->evaluate(tu));
	printLine("\nTyp: ");
	printLine(Enums::TERRITORIAL_UNIT_TYPEtoString(this->cType_->evaluate(tu)));
	printLine("\n");

	printLine("Vzdelanie: ");
	printLine(Enums::EDUCATION_TYPEtoString(educationType));
	printLine("\tPocet: ");
	printLine(this->cEduCount_->evaluate(tu));
	printLine("\n");

	printLine("Ekonomicka vekova skupina: ");
	printLine(Enums::ECONOMIC_AGE_GROUPtoString(ageGroupType));
	printLine("\tPocet: ");
	printLine(this->cAgeGroupCount_->evaluate(tu));
	printLine("\n");

	TerritorialUnit* superiorTu = &tu->getSuperiorTU();
	if (superiorTu != nullptr)
	{
		printLine("Vyssie uzemne celky: \n");
	}
	while (superiorTu != nullptr)
	{
		printLine("Nazov: ");
		printLine(this->cTitle_->evaluate(superiorTu));
		printLine("\tTyp: ");
		printLine(Enums::TERRITORIAL_UNIT_TYPEtoString(this->cType_->evaluate(superiorTu)));
		printLine("\n");
		superiorTu = &superiorTu->getSuperiorTU();
	}
	pressEnter();
}

void App::runFilters()
{
	printLine("\n--- Filtrovanie ---\n");

	int input;
	Enums::TERRITORIAL_UNIT_TYPE tuType = Enums::ALL;
	TerritorialUnit* superiorTU = nullptr;
	bool useCEduCount = false, useCEduRatio = false, useCAgeCount = false, useCAgeRatio = false, useCAgeGroupCount = false, useCAgeGroupRatio = false;
	do
	{
		
		int min = 0, max = 0, age = 0;
		double minD = 0.0, maxD = 0.0;
		Enums::EDUCATION_TYPE educationType;
		Enums::ECONOMIC_AGE_GROUP ageGroup;
		Enums::GENDER gender;

		printLine("Vyberte filtre:\n");
		printLine("1. UJVzdelaniePocet\n");
		printLine("2. UJVzdelaniePodiel\n");
		printLine("3. UJTyp\n");
		printLine("4. UJPrislusnost\n");
		printLine("5. UJVekPocet\n");
		printLine("6. UJVekPodiel\n");
		printLine("7. UJVekovaSkupinaPocet\n");
		printLine("8. UJVekovaSkupinaPodiel\n");
		printLine("0. Pokracovat\n");
		input = this->readInt(0, 8);

		switch (input)
		{
		case 1:
			educationType = this->chooseEducationType();
			min = this->chooseIntMin();
			max = this->chooseIntMax();
			this->fEducationCount_->changeEducationType(educationType);
			this->fEducationCount_->changeInterval(min, max);
			this->cEduCount_->changeEducationType(educationType);
			this->compositeFilter_->registerFilter(fEducationCount_);
			useCEduCount = true;
			break;
		case 2:
			educationType = this->chooseEducationType();
			minD = this->chooseDoubleMin();
			maxD = this->chooseDoubleMax();
			this->fEducationRatio_->changeEducationType(educationType);
			this->fEducationRatio_->changeInterval(minD, maxD);
			this->compositeFilter_->registerFilter(this->fEducationRatio_);
			this->cEduRatio_->changeEducationType(educationType);
			useCEduRatio = true;
			break;
		case 3:
			tuType = this->chooseTUType(false);
			this->fType_->changeValue(tuType);
			this->compositeFilter_->registerFilter(this->fType_);
			break;
		case 4:
			superiorTU = this->chooseTU();
			this->fJurisdiction_->changeSuperiorTU(superiorTU);
			this->compositeFilter_->registerFilter(fJurisdiction_);
			break;
		case 5:
			gender = this->chooseGender();
			age = this->chooseAge();
			min = this->chooseIntMin();
			max = this->chooseIntMax();
			this->fAgeCount_->changeAge(age);
			this->fAgeCount_->changeGender(gender);
			this->fAgeCount_->changeInterval(min, max);
			this->compositeFilter_->registerFilter(fAgeCount_);
			this->cAgeCount_->changeAge(age);
			this->cAgeCount_->changeAge(gender);
			useCAgeCount = true;
			break;
		case 6:
			gender = this->chooseGender();
			age = chooseAge();
			minD = this->chooseDoubleMin();
			maxD = this->chooseDoubleMax();
			this->fAgeRatio_->changeAge(age);
			this->fAgeRatio_->changeGender(gender);
			this->fAgeRatio_->changeInterval(minD, maxD);
			this->compositeFilter_->registerFilter(fAgeRatio_);
			this->cAgeRatio_->changeAge(age);
			this->cAgeRatio_->changeAge(gender);
			useCAgeRatio = true;
			break;
		case 7:
			ageGroup = this->chooseEconomicAgeGroup();
			min = this->chooseIntMin();
			max = this->chooseIntMax();
			this->fAgeGroupCount_->changeEconomicAgeGroup(ageGroup);
			this->fAgeGroupCount_->changeInterval(min, max);
			this->compositeFilter_->registerFilter(fAgeGroupCount_);
			this->cAgeGroupCount_->changeAgeGroup(ageGroup);
			useCAgeGroupCount = true;
			break;
		case 8:
			ageGroup = this->chooseEconomicAgeGroup();
			minD = this->chooseDoubleMin();
			maxD = this->chooseDoubleMax();
			this->fAgeGroupRatio_->changeEconomicAgeGroup(ageGroup);
			this->fAgeGroupRatio_->changeInterval(minD, maxD);
			this->compositeFilter_->registerFilter(fAgeGroupRatio_);
			this->cAgeGroupRatio_->changeAgeGroup(ageGroup);
			useCAgeGroupRatio = true;
			break;
		}
		printLine("\n");
	} while (input != 0);

	this->record_->getFilteredTable(tuType, *this->compositeFilter_, *this->finalTable_, superiorTU);
	printLine("\nPouzite filtre:\n");
	printLine(this->compositeFilter_->toString());
	printLine("\nNajdene uzemne jednotky:\n");
	if (this->finalTable_->isEmpty())
	{
		printLine("Nepodarilo sa najst ziadnu uzemnu jednotku vyhovujucu danym filtrom\n");
	}
	else
	{
		CriterionTUTitle cTitle;
		CriterionTUType cType;
		for (auto item : *this->finalTable_)
		{
			TerritorialUnit* tu = item->accessData();
			printLine("Nazov: ");
			printLine(cTitle.evaluate(tu));
			printLine("\nTyp: ");
			printLine(Enums::TERRITORIAL_UNIT_TYPEtoString(cType.evaluate(tu)));
			printLine("\n");
			
			if (useCEduCount)
			{
				printLine("Vzdelanie pocet: ");
				printLine(this->cEduCount_->evaluate(tu));
				printLine("\n");
			}
			if (useCEduRatio)
			{
				printLine("Vzdelanie podiel: ");
				printLine(this->cEduRatio_->evaluate(tu));
				printLine("\n");
			}
			if (useCAgeCount)
			{
				printLine("Vek pocet: ");
				printLine(this->cAgeCount_->evaluate(tu));
				printLine("\n");
			}
			if (useCAgeRatio) 
			{
				printLine("Vek podiel: ");
				printLine(this->cAgeRatio_->evaluate(tu));
				printLine("\n");
			}
			if (useCAgeGroupCount)
			{
				printLine("Vekova skupina pocet: ");
				printLine(this->cAgeGroupCount_->evaluate(tu));
				printLine("\n");
			}
			if (useCAgeGroupRatio)
			{
				printLine("Vekova skupina podiel: ");
				printLine(this->cAgeGroupRatio_->evaluate(tu));
				printLine("\n");
			}

			TerritorialUnit* superiorTu = &tu->getSuperiorTU();
			if (superiorTu != nullptr)
			{
				printLine("Vyssie uzemne celky: \n");
			}
			while (superiorTu != nullptr)
			{
				printLine("Nazov: ");
				printLine(cTitle.evaluate(superiorTu));
				printLine("\tTyp: ");
				printLine(Enums::TERRITORIAL_UNIT_TYPEtoString(cType.evaluate(superiorTu)));
				printLine("\n");
				superiorTu = &superiorTu->getSuperiorTU();
			}
			printLine("\n");
		}
	}
	pressEnter();
	this->finalTable_->clear();
	this->compositeFilter_->clear();
}

void App::runSorting()
{
	printLine("\n--- Triedenie ---\n");

	int input;
	Enums::TERRITORIAL_UNIT_TYPE tuType = Enums::ALL;
	Enums::EDUCATION_TYPE educationType = Enums::UNKNOWN;
	Enums::GENDER gender = Enums::UNSPECIFIED_GENDER;
	Enums::ECONOMIC_AGE_GROUP ageGroup = Enums::UNSPECIFIED;
	int age = 0;
	bool ascending;
	TerritorialUnit* superiorTU = nullptr;

	printLine("Zvolte kriterium pre triedenie:\n");
	printLine("1. Nazov\n");
	printLine("2. UJVzdelaniePocet\n");
	printLine("3. UJVzdelaniePodiel\n");
	printLine("4. UJVekPodiel\n");
	printLine("5. UJVekovaSkupinaPocet\n");
	const int task = this->readInt(1, 5);
	printLine("\n");

	switch (task)
	{
	case 2:
		educationType = this->chooseEducationType();
		this->cEduCount_->changeEducationType(educationType);
		break;
	case 3:
		educationType = this->chooseEducationType();
		this->cEduRatio_->changeEducationType(educationType);
		break;
	case 4:
		gender = this->chooseGender();
		age = this->chooseAge();
		this->cAgeRatio_->changeGender(gender);
		this->cAgeRatio_->changeAge(age);
		this->cAgeCount_->changeGender(gender);
		this->cAgeCount_->changeAge(age);
		break;
	case 5:
		ageGroup = this->chooseEconomicAgeGroup();
		this->cAgeGroupCount_->changeAgeGroup(ageGroup);
		this->cAgeGroupRatio_->changeAgeGroup(ageGroup);
		break;
	}

	ascending = this->chooseAscending();

	do
	{
		printLine("Vyberte filtre:\n");
		printLine("1. UJTyp\n");
		printLine("2. UJPrislusnost\n");
		switch (task)
		{
		case 2:
			printLine("3. UJVzdelaniePocet\n");
			break;
		case 3:
			printLine("3. UJVzdelaniePodiel\n");
			break;
		case 4:
			printLine("3. UJVekPodiel\n");
			break;
		case 5:
			printLine("3. UJVekovaSkupinaPocet\n");
			break;
		}
		printLine("0. Pokracovat\n");
		input = this->readInt(0, 3);

		switch (input)
		{
		case 1:
			tuType = this->chooseTUType(false);
			this->fType_->changeValue(tuType);
			this->compositeFilter_->registerFilter(this->fType_);
			break;
		case 2:
			superiorTU = this->chooseTU();
			this->fJurisdiction_->changeSuperiorTU(superiorTU);
			this->compositeFilter_->registerFilter(this->fJurisdiction_);
			break;
		case 3:
			int min, max;
			double minD, maxD;
			switch (task)
			{
			case 2:
				min = this->chooseIntMin();
				max = this->chooseIntMax();
				this->fEducationCount_->changeEducationType(educationType);
				this->fEducationCount_->changeInterval(min, max);
				this->compositeFilter_->registerFilter(this->fEducationCount_);
				break;
			case 3:
				minD = this->chooseDoubleMin();
				maxD = this->chooseDoubleMax();
				this->fEducationRatio_->changeEducationType(educationType);
				this->fEducationRatio_->changeInterval(minD, maxD);
				this->compositeFilter_->registerFilter(this->fEducationRatio_);
				break;
			case 4:
				minD = this->chooseDoubleMin();
				maxD = this->chooseDoubleMax();
				this->fAgeRatio_->changeAge(age);
				this->fAgeRatio_->changeGender(gender);
				this->fAgeRatio_->changeInterval(minD, maxD);
				this->compositeFilter_->registerFilter(this->fAgeRatio_);
				break;
			case 5:
				
				min = this->chooseIntMin();
				max = this->chooseIntMax();
				this->fAgeGroupCount_->changeEconomicAgeGroup(ageGroup);
				this->fAgeGroupCount_->changeInterval(min, max);
				this->compositeFilter_->registerFilter(this->fAgeGroupCount_);
				break;
			}

			break;
		}
	} while (input != 0);
	
	this->record_->getFilteredTable(tuType, *this->compositeFilter_, *this->finalTable_, superiorTU);

	switch (task)
	{
	case 1:
		structures::QuickSort<std::wstring, TerritorialUnit*, std::wstring>().sort(*this->finalTable_, *this->cTitle_, ascending);
		break;
	case 2:
		structures::QuickSort<std::wstring, TerritorialUnit*, int>().sort(*this->finalTable_, *this->cEduCount_, ascending);
		break;
	case 3:
		structures::QuickSort<std::wstring, TerritorialUnit*, double>().sort(*this->finalTable_, *this->cEduRatio_, ascending);
		break;
	case 4:
		structures::QuickSort<std::wstring, TerritorialUnit*, double>().sort(*this->finalTable_, *this->cAgeRatio_, ascending);
		break;
	case 5:
		structures::QuickSort<std::wstring, TerritorialUnit*, int>().sort(*this->finalTable_, *this->cAgeGroupCount_, ascending);
		break;
	}
	
	if (this->finalTable_->isEmpty())
	{
		printLine("Nepodarilo sa najst ziadnu uzemnu jednotku vyhovujucu danym filtrom\n");
	}
	else
	{
		printLine("\n\nUtriedeny zoznam uzemnych jednotiek:\n\n");
		for (auto item : *this->finalTable_)
		{
			TerritorialUnit* tu = item->accessData();
			printLine("Nazov: ");
			printLine(CriterionTUTitle().evaluate(tu));
			printLine("\n");
			switch (task)
			{
			case 2:
				printLine("Vzdelanie pocet: ");
				printLine(this->cEduCount_->evaluate(tu));
				printLine("\n");
				break;
			case 3:
				printLine("Vzdelanie podiel: ");
				printLine(this->cEduRatio_->evaluate(tu));
				printLine("\n");
				break;
			case 4:
				printLine("Vek: ");
				printLine(age);
				printLine(", Pocet: ");
				printLine(this->cAgeCount_->evaluate(tu));
				printLine(", Podiel: ");
				printLine(this->cAgeRatio_->evaluate(tu));
				printLine("\n");
				break;
			case 5:
				printLine("Vekova skupina: ");
				printLine(Enums::ECONOMIC_AGE_GROUPtoString(ageGroup));
				printLine(", Pocet: ");
				printLine(this->cAgeGroupCount_->evaluate(tu));
				printLine(", Podiel: ");
				printLine(this->cAgeGroupRatio_->evaluate(tu));
				printLine("\n");
				break;
			}
		}
	}
	pressEnter();
	this->finalTable_->clear();
	this->compositeFilter_->clear();
}

void App::runSelect()
{
	printLine("\n--- Vyber najlepsich ---\n");

	TerritorialUnit* superiorTU = nullptr;
	int input;
	Enums::TERRITORIAL_UNIT_TYPE tuType = Enums::ALL;
	Enums::ECONOMIC_AGE_GROUP ageGroup = Enums::PRODUCTIVE;

	printLine("Zvolte vyberove kriterium:\n");
	printLine("1. NajvacsiaVekovaSkupina\n");
	printLine("2. NajmensiaVekovaSkupina\n");
	const int type = this->readInt(1, 2);
	printLine("\n");
	ageGroup = this->chooseEconomicAgeGroup();

	do
	{
		printLine("Vyberte filtre:\n");
		printLine("1. UJTyp\n");
		printLine("2. UJPrislusnost\n");
		printLine("0. Pokracovat\n");
		input = this->readInt(0, 2);
		switch (input)
		{
		case 1:
			tuType = this->chooseTUType(false);
			this->fType_->changeValue(tuType);
			this->compositeFilter_->registerFilter(this->fType_);
			break;
		case 2:
			superiorTU = this->chooseTU();
			this->fJurisdiction_->changeSuperiorTU(superiorTU);
			this->compositeFilter_->registerFilter(this->fJurisdiction_);
			break;
		}

	} while (input != 0);

	this->record_->getFilteredTable(tuType, *this->compositeFilter_, *this->finalTable_, superiorTU);
	this->sCriterionMinAgeGroup_->changeAgeGroup(ageGroup);
	this->sCriterionMaxAgeGroup_->changeAgeGroup(ageGroup);
	this->cAgeGroupCount_->changeAgeGroup(ageGroup);
	TerritorialUnit*& bestTU = type == 1 ? this->sCriterionMaxAgeGroup_->selectBest(this->finalTable_) : this->sCriterionMinAgeGroup_->selectBest(this->finalTable_);
	printLine("\nNajlepsia uzemna jednotka:\n");
	printLine("Nazov: ");
	printLine(this->cTitle_->evaluate(bestTU));
	printLine("\nTyp: ");
	printLine(Enums::TERRITORIAL_UNIT_TYPEtoString(this->cType_->evaluate(bestTU)));
	printLine("\nVekova skupina: ");
	printLine(Enums::ECONOMIC_AGE_GROUPtoString(ageGroup));
	printLine(", Pocet: ");
	printLine(this->cAgeGroupCount_->evaluate(bestTU));
	pressEnter();
	this->finalTable_->clear();
	this->compositeFilter_->clear();
}

int App::readInt()
{
	int result;
	std::wstring str;
	bool pass = false;
	do
	{
		str = this->readString();
		std::wistringstream stream(str);
		stream >> result;
		if (!stream.fail() && stream.eof())
		{
			pass = true;
		}
		else
		{
			printLine("Zla hodnota\n");
		}
	} while (!pass);
	return result;
}

int App::readInt(int min, int max)
{
	int result;
	bool pass;
	do
	{
		pass = true;
		result = this->readInt();
		if (min > result || max < result)
		{
			printLine("Zla hodnota\n");
			pass = false;
		}
	} while (!pass);
	return result;
}

double App::readDouble()
{
	double result;
	std::wstring str;
	bool pass = false;
	do
	{
		str = this->readString();
		std::wistringstream stream(str);
		stream >> result;
		if (!stream.fail() && stream.eof())
		{
			pass = true;
		}
		else
		{
			printLine("Zla hodnota\n");
		}
	} while (!pass);
	return result;
}

std::wstring App::readString()
{
	std::wstring str;
	do
	{
		std::getline(std::wcin, str);
	} while (str.size() <= 0);
	return str;
}

Enums::EDUCATION_TYPE App::chooseEducationType()
{
	printLine("Zvolte typ vzdelania:\n");
	printLine("1. ");
	printLine(Enums::EDUCATION_TYPEtoString(Enums::WITHOUT_COMPLETED));
	printLine("\n2. ");
	printLine(Enums::EDUCATION_TYPEtoString(Enums::PRIMARY));
	printLine("\n3. ");
	printLine(Enums::EDUCATION_TYPEtoString(Enums::APPRENTICESHIP));
	printLine("\n4. ");
	printLine(Enums::EDUCATION_TYPEtoString(Enums::SECONDARY));
	printLine("\n5. ");
	printLine(Enums::EDUCATION_TYPEtoString(Enums::HIGHER));
	printLine("\n6. ");
	printLine(Enums::EDUCATION_TYPEtoString(Enums::UNIVERSITY));
	printLine("\n7. ");
	printLine(Enums::EDUCATION_TYPEtoString(Enums::WITHOUT_EDUCATION));
	printLine("\n8. ");
	printLine(Enums::EDUCATION_TYPEtoString(Enums::UNKNOWN));
	printLine("\n");
	int input = this->readInt(1, 8);
	printLine("\n");
	return static_cast<Enums::EDUCATION_TYPE>(input - 1);
}

Enums::ECONOMIC_AGE_GROUP App::chooseEconomicAgeGroup()
{
	printLine("Zvolte ekonomicku vekovu skupinu:\n");
	printLine("1. ");
	printLine(Enums::ECONOMIC_AGE_GROUPtoString(Enums::PRE_PRODUCTIVE));
	printLine("\n2. ");
	printLine(Enums::ECONOMIC_AGE_GROUPtoString(Enums::PRODUCTIVE));
	printLine("\n3. ");
	printLine(Enums::ECONOMIC_AGE_GROUPtoString(Enums::POST_PRODUCTIVE));
	printLine("\n");
	int ageGroup = this->readInt(1, 3);
	printLine("\n");
	return static_cast<Enums::ECONOMIC_AGE_GROUP>(ageGroup - 1);
}

Enums::TERRITORIAL_UNIT_TYPE App::chooseTUType(bool enableALL)
{
	int max = enableALL ? 5: 4;
	printLine("Zvolte typ uzemnej jednotky:\n");
	printLine("1. ");
	printLine(Enums::TERRITORIAL_UNIT_TYPEtoString(Enums::MUNICIPALITY));
	printLine("\n2. ");
	printLine(Enums::TERRITORIAL_UNIT_TYPEtoString(Enums::DISTRICT));
	printLine("\n3. ");
	printLine(Enums::TERRITORIAL_UNIT_TYPEtoString(Enums::REGION));
	printLine("\n4. ");
	printLine(Enums::TERRITORIAL_UNIT_TYPEtoString(Enums::STATE));
	if (enableALL)
	{
		printLine("\n5. ");
		printLine(Enums::TERRITORIAL_UNIT_TYPEtoString(Enums::ALL));
	}
	printLine("\n");
	int input = this->readInt(1, max);
	printLine("\n");
	return static_cast<Enums::TERRITORIAL_UNIT_TYPE>(input - 1);
}

Enums::GENDER App::chooseGender()
{
	printLine("Zvolte pohlavie:\n");
	printLine("1. ");
	printLine(Enums::GENDERtoString(Enums::MEN));
	printLine("\n2. ");
	printLine(Enums::GENDERtoString(Enums::WOMEN));
	printLine("\n3. ");
	printLine(Enums::GENDERtoString(Enums::UNSPECIFIED_GENDER));
	printLine("\n");
	int input = this->readInt(1, 3);
	printLine("\n");
	return static_cast<Enums::GENDER>(input - 1);
}

TerritorialUnit* App::chooseTU()
{
	TerritorialUnit* tu;
	std::wstring title;
	bool pass;
	do
	{
		pass = true;
		printLine("Nazov uzemnej jednotky:\n");
		title = this->readString();
		printLine("\n");

		if (!this->record_->getAllTerritorialUnits().tryFind(title, tu))
		{
			printLine("Uzemna jednotka s danym nazvom sa nenachadza v datach.\n");
			pass = false;
		}
	} while (!pass);

	return tu;
}

bool App::chooseAscending()
{
	printLine("Zvolte sposob triedenia:\n");
	printLine("1. Vzostupne\n");
	printLine("2. Zostupne\n");
	bool val = this->readInt(1, 2) == 1;
	printLine("\n");
	return val;
}

int App::chooseAge()
{
	printLine("Zvolte vek (0-100):\n");
	int val = this->readInt(0, 100);
	printLine("\n");
	return val;
}

int App::chooseIntMin()
{
	printLine("Zvolte minimum:\n");
	int val = this->readInt();
	printLine("\n");
	return val;
}

int App::chooseIntMax()
{
	printLine("Zvolte maximum:\n");
	int val = this->readInt();
	printLine("\n");
	return val;
}

double App::chooseDoubleMin()
{
	printLine("Zvolte minimum (desatinne cislo):\n");
	double val =  this->readDouble();
	printLine("\n");
	return val;
}

double App::chooseDoubleMax()
{
	printLine("Zvolte maximum (desatinne cislo):\n");
	double val = this->readDouble();
	printLine("\n");
	return val;
}


void App::printLine(std::string line)
{
	std::cout << line;
}

void App::printLine(std::wstring line)
{
	std::wcout << line;
}

void App::printLine(int line)
{
	std::cout << line;
}

void App::printLine(double line)
{
	std::cout << std::fixed << std::setprecision(2) << line;
}

void App::pressEnter()
{
	printLine("\nPre pokracovanie stlacte klavesu ENTER ");
	std::wstring str;
	std::getline(std::wcin, str);
	printLine("\n\n");
}
