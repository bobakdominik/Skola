#include "district.h"
#include "region.h"

District::District(const std::wstring code, const std::wstring officialTitle, const std::wstring mediumTitle, const std::wstring shortTitle, const std::wstring note) :
	TerritorialUnit(code, officialTitle, mediumTitle, shortTitle, note, Enums::DISTRICT),
	municipalities_(new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>())
{
}

District::~District()
{
	delete this->municipalities_;
	this->municipalities_ = nullptr;
}

void District::setSuperiorTU(TerritorialUnit* superiorTU)
{
	Region& region = dynamic_cast<Region&>(*superiorTU);
	this->superiorTU_ = superiorTU;
	region.addDistrict(this);
}

structures::Table<std::wstring, TerritorialUnit*>& District::getMunicipalitiest()
{
	return *this->municipalities_;
}

structures::Table<std::wstring, TerritorialUnit*>& District::getSubordinateTUs()
{
	return *this->municipalities_;
}

void District::addMunicipality(Municipality* municipality)
{
	if (municipality != nullptr)
	{
		this->municipalities_->insert(municipality->getOfficialTitle(), municipality);
		*this->education_ += municipality->getEducation();
		*this->age_ += municipality->getAge();
		if (this->superiorTU_ != nullptr)
		{
			Region* region = static_cast<Region*>(this->superiorTU_);
			region->addMunicipality(municipality);
		}
	}
}
