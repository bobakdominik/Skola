#pragma once
#include <string>


class Enums {
public:

	enum TERRITORIAL_UNIT_TYPE
	{
		MUNICIPALITY,
		DISTRICT,
		REGION,
		STATE,
		ALL
	};

	enum EDUCATION_TYPE
	{
		WITHOUT_COMPLETED,
		PRIMARY,
		APPRENTICESHIP,
		SECONDARY,
		HIGHER,
		UNIVERSITY,
		WITHOUT_EDUCATION,
		UNKNOWN
	};

	enum DATA_TYPE
	{
		MUNICIPALITIES,
		DISTRICTS,
		REGIONS,
		STATES,
		EDUCATION
	};

	enum ECONOMIC_AGE_GROUP {
		PRE_PRODUCTIVE,
		PRODUCTIVE,
		POST_PRODUCTIVE,
		UNSPECIFIED
	};

	enum GENDER {
		MEN,
		WOMEN,
		UNSPECIFIED_GENDER
	};

	inline static std::wstring TERRITORIAL_UNIT_TYPEtoString(Enums::TERRITORIAL_UNIT_TYPE tuType) {
		switch (tuType)
		{
		case Enums::MUNICIPALITY:
			return L"Obec";
		case Enums::DISTRICT:
			return L"Okres";
		case Enums::REGION:
			return L"Kraj";
		case Enums::STATE:
			return L"Stat";
		case Enums::ALL:
			return L"Nespecifikovane";
		default:
			return L"";
		}
	};

	inline static std::wstring EDUCATION_TYPEtoString(Enums::EDUCATION_TYPE educationType) {
		switch (educationType)
		{
		case Enums::WITHOUT_COMPLETED:
			return L"Bez ukonceneho vzdelania";
		case Enums::PRIMARY:
			return L"Zakladne";
		case Enums::APPRENTICESHIP:
			return L"Ucnovske";
		case Enums::SECONDARY:
			return L"Stredne";
		case Enums::HIGHER:
			return L"Vyssie";
		case Enums::UNIVERSITY:
			return L"Vysokoskolske";
		case Enums::WITHOUT_EDUCATION:
			return L"Bez vzdelania";
		case Enums::UNKNOWN:
		default:
			return L"Nezistene";
		}
	};

	inline static std::wstring DATA_TYPEtoString(Enums::DATA_TYPE dataType) {
		switch (dataType)
		{
		case Enums::MUNICIPALITIES:
			return L"Obce";
		case Enums::DISTRICTS:
			return L"Okresy";
		case Enums::REGIONS:
			return L"Regiony";
		case Enums::STATES:
			return L"Staty";
		case Enums::EDUCATION:
			return L"Vzdelanie";
		default:
			return L"";
		}
	};

	inline static std::wstring ECONOMIC_AGE_GROUPtoString(Enums::ECONOMIC_AGE_GROUP ageGroup) {
		switch (ageGroup)
		{
		case Enums::PRE_PRODUCTIVE:
			return L"Predproduktivni";
		case Enums::PRODUCTIVE:
			return L"Produktivni";
		case Enums::POST_PRODUCTIVE:
			return L"Poproduktivni";
		case Enums::UNSPECIFIED:
		default:
			return L"Nespecifikovane";
		}
	};

	inline static std::wstring GENDERtoString(Enums::GENDER gender) {
		switch (gender)
		{
		case Enums::MEN:
			return L"Muzske";
		case Enums::WOMEN:
			return L"Zenske";
		case Enums::UNSPECIFIED_GENDER:
		default:
			return L"Nespecifikovane";
		}
	};
};







