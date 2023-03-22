#pragma once
#include "enums.h"
#include "structures/array/array.h"

class Age
{
public:
	Age();
	~Age();

	void addAge(Enums::GENDER gender, structures::Array<int>& ages);
	int getEconomicAgeCount(Enums::GENDER gender, Enums::ECONOMIC_AGE_GROUP ageGroup);
	int getAgeCount(Enums::GENDER gender, int ageCategory);
	structures::Array<int>& getAllAges(Enums::GENDER gender);

	Age& operator+=(Age& other);
private:
	structures::Array<int>* men_;
	structures::Array<int>* women_;
};

