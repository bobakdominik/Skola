#pragma once

#include "enums.h"

class Education
{
public:
	Education();
	Education(int withoutCompletedEducation,
	int primaryEducation,
	int apprenticeshipEducation,
	int secondaryEducation,
	int higherEducation,
	int universityEducation,
	int withoutEducation,
	int unknown);
	Education(Education& other);
	~Education();

	int getEducationCount(Enums::EDUCATION_TYPE type);

	void addEducationCount(int count, Enums::EDUCATION_TYPE type);
	Education& operator+=(Education& other);
private:
	int withoutCompletedEducation_;
	int primaryEducation_;
	int apprenticeshipEducation_;
	int secondaryEducation_;
	int higherEducation_;
	int universityEducation_;
	int withoutEducation_;
	int unknown_;
};


