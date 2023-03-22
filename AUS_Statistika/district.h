#pragma once
#include<string>
#include "territorialUnit.h"
#include "structures/table/sorted_sequence_table.h"
#include "municipality.h"

class District :
    public TerritorialUnit
{
public:
    District(const std::wstring code,
        const std::wstring officialTitle,
        const std::wstring mediumTitle,
        const std::wstring shortTitle,
        const std::wstring note);
    ~District();

    void setSuperiorTU(TerritorialUnit* superiorTU) override;

    structures::Table<std::wstring, TerritorialUnit*>& getMunicipalitiest();
    structures::Table<std::wstring, TerritorialUnit*>& getSubordinateTUs();
    void addMunicipality(Municipality* municipality);

private:

    structures::Table<std::wstring, TerritorialUnit*>* municipalities_;
};

