#include "state.h"
#include "structures/table/sorted_sequence_table.h"

State::State(const std::wstring code, const std::wstring officialTitle, const std::wstring mediumTitle, const std::wstring shortTitle, const std::wstring note):
	TerritorialUnit(code, officialTitle, mediumTitle, shortTitle, note, Enums::STATE),
	municipalities_(new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>()),
	districts_(new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>()),
	regions_(new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>()),
	subordinateTUs_(new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>())
{
}

State::~State()
{
	delete this->districts_;
	delete this->regions_;
	delete this->municipalities_;
	delete this->subordinateTUs_;

	this->districts_ = nullptr;
	this->regions_ = nullptr;
	this->municipalities_ = nullptr;
	this->subordinateTUs_ = nullptr;
}

void State::setSuperiorTU(TerritorialUnit* superiorTU)
{
	TerritorialUnit* tu = superiorTU; //Pre zbavenie sa warningu
	tu = nullptr;
	throw std::logic_error("State::setSuperiorTU: No superior territorial unit for state.");
}

structures::Table<std::wstring, TerritorialUnit*>& State::getMunicipalitiest()
{
	return *this->municipalities_;
}

structures::Table<std::wstring, TerritorialUnit*>& State::getDistricts()
{
	return *this->districts_;
}

structures::Table<std::wstring, TerritorialUnit*>& State::getRegions()
{
	return *this->regions_;
}

structures::Table<std::wstring, TerritorialUnit*>& State::getSubordinateTUs()
{
	return *this->subordinateTUs_;
}

void State::addMunicipality(Municipality* municipality)
{
	if (municipality != nullptr)
	{
		this->municipalities_->insert(municipality->getOfficialTitle(), municipality);
		this->subordinateTUs_->insert(municipality->getOfficialTitle(), municipality);
		*this->education_ += municipality->getEducation();
		*this->age_ += municipality->getAge();
		if (this->superiorTU_ != nullptr)
		{
			State* state = static_cast<State*>(this->superiorTU_);
			state->addMunicipality(municipality);
		}
	}
}

void State::addDistrict(District* district)
{
	if (district != nullptr)
	{
		this->districts_->insert(district->getOfficialTitle(), district);
		this->subordinateTUs_->insert(district->getOfficialTitle(), district);
		*this->education_ += district->getEducation();
		*this->age_ += district->getAge();
		for (auto municipality : district->getMunicipalitiest())
		{
			this->municipalities_->insert(municipality->accessData()->getOfficialTitle(), municipality->accessData());
			this->subordinateTUs_->insert(municipality->accessData()->getOfficialTitle(), municipality->accessData());
		}
	}
}

void State::addRegion(Region* region)
{
	if (region != nullptr)
	{
		this->regions_->insert(region->getOfficialTitle(), region);
		this->subordinateTUs_->insert(region->getOfficialTitle(), region);
		*this->education_ += region->getEducation();
		*this->age_ += region->getAge();
		for (auto municipality : region->getMunicipalitiest())
		{
			this->municipalities_->insert(municipality->accessData()->getOfficialTitle(), municipality->accessData());
			this->subordinateTUs_->insert(municipality->accessData()->getOfficialTitle(), municipality->accessData());
		}
		for (auto district : region->getDistricts())
		{
			this->districts_->insert(district->accessData()->getOfficialTitle(), district->accessData());
			this->subordinateTUs_->insert(district->accessData()->getOfficialTitle(), district->accessData());
		}
	}
}
