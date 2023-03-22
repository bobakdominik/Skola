#pragma once

#include <string>
#include "enums.h"
#include "education.h"
#include "age.h"

class TerritorialUnit
{
public:

	virtual ~TerritorialUnit();

	std::wstring getCode();
	std::wstring getOfficialTitle();
	std::wstring getMediumTitle();
	std::wstring getShortTitle();
	std::wstring getNote();
	TerritorialUnit& getSuperiorTU();
	Enums::TERRITORIAL_UNIT_TYPE getTypeTU();
	Education& getEducation();
	Age& getAge();
	int getNumberOfCitizens();

	virtual void setSuperiorTU(TerritorialUnit* superiorTU) = 0;
	void addEducation(Education& education);
	void addAge(Age& age);

protected:
	
	TerritorialUnit(const std::wstring code, 
		const std::wstring officialTitle,
		const std::wstring mediumTitle, 
		const std::wstring shortTitle,
		const std::wstring note,
		const Enums::TERRITORIAL_UNIT_TYPE typeTU);
	
	TerritorialUnit* superiorTU_;
	Education* education_;
	Age* age_;
private:

	const std::wstring code_;
	const std::wstring officialTitle_;
	const std::wstring mediumTitle_;
	const std::wstring shortTitle_;
	const std::wstring note_;
	const Enums::TERRITORIAL_UNIT_TYPE typeTU_;
	
	
};

