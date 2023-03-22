#pragma once
#include "territorialUnit.h"
#include "structures/table/sorted_sequence_table.h"
#include "municipality.h"
#include "district.h"
#include "region.h"

class State :
    public TerritorialUnit
{
public:
    State(const std::wstring code,
        const std::wstring officialTitle,
        const std::wstring mediumTitle,
        const std::wstring shortTitle,
        const std::wstring note);
    ~State();

    void setSuperiorTU(TerritorialUnit* superiorTU) override;

    structures::Table<std::wstring, TerritorialUnit*>& getMunicipalitiest();
    structures::Table<std::wstring, TerritorialUnit*>& getDistricts();
    structures::Table<std::wstring, TerritorialUnit*>& getRegions();
    structures::Table<std::wstring, TerritorialUnit*>& getSubordinateTUs();

    void addMunicipality(Municipality* municipality);
    void addDistrict(District* district);
    void addRegion(Region* region);

private:

    structures::Table<std::wstring, TerritorialUnit*>* municipalities_;
    structures::Table<std::wstring, TerritorialUnit*>* districts_;
    structures::Table<std::wstring, TerritorialUnit*>* regions_;
    structures::Table<std::wstring, TerritorialUnit*>* subordinateTUs_;
};

