#include "territorialUnit.h"


TerritorialUnit::TerritorialUnit(const std::wstring code, const std::wstring officialTitle, const std::wstring mediumTitle, const std::wstring shortTitle, const std::wstring note, const Enums::TERRITORIAL_UNIT_TYPE typeTU) :
	code_(code),
	officialTitle_(officialTitle),
	mediumTitle_(mediumTitle),
	shortTitle_(shortTitle),
	note_(note),
	typeTU_(typeTU),
	education_(new Education()),
	superiorTU_(nullptr),
	age_(new Age())
{
}

TerritorialUnit::~TerritorialUnit()
{
	delete this->education_;
	delete this->age_;
	this->education_ = nullptr;
	this->superiorTU_ = nullptr;
	this->age_ = nullptr;
}

std::wstring TerritorialUnit::getCode()
{
	return this->code_;
}

std::wstring TerritorialUnit::getOfficialTitle()
{
	return this->officialTitle_;
}

std::wstring TerritorialUnit::getMediumTitle()
{
	return this->mediumTitle_;
}

std::wstring TerritorialUnit::getShortTitle()
{
	return this->shortTitle_;
}

std::wstring TerritorialUnit::getNote()
{
	return this->note_;
}

TerritorialUnit& TerritorialUnit::getSuperiorTU()
{
	return *this->superiorTU_;
}

Enums::TERRITORIAL_UNIT_TYPE TerritorialUnit::getTypeTU()
{
	return this->typeTU_;
}

Education& TerritorialUnit::getEducation()
{
	return *this->education_;
}

Age& TerritorialUnit::getAge()
{
	return *this->age_;
}

int TerritorialUnit::getNumberOfCitizens()
{
	return this->age_->getEconomicAgeCount(Enums::GENDER::UNSPECIFIED_GENDER, Enums::ECONOMIC_AGE_GROUP::UNSPECIFIED);
}

void TerritorialUnit::addEducation(Education& education)
{
	if (this->education_ != nullptr)
	{
		*this->education_ += education;
	}
	else
	{
		this->education_ = new Education(education);
	}
	if (this->superiorTU_ != nullptr)
	{
		this->superiorTU_->addEducation(education);
	}
}

void TerritorialUnit::addAge(Age& age)
{
	*this->age_ += age;
	if (this->superiorTU_ != nullptr)
	{
		this->superiorTU_->addAge(age);
	}
}
