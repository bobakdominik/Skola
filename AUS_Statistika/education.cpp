#include "education.h"

Education::Education():
	withoutCompletedEducation_(0),
	primaryEducation_(0),
	apprenticeshipEducation_(0),
	secondaryEducation_(0),
	higherEducation_(0),
	universityEducation_(0),
	withoutEducation_(0),
	unknown_(0)
{
}

Education::Education(int withoutCompletedEducation,
	int primaryEducation,
	int apprenticeshipEducation,
	int secondaryEducation,
	int higherEducation,
	int universityEducation,
	int withoutEducation,
	int unknown) :
	withoutCompletedEducation_(withoutCompletedEducation),
	primaryEducation_(primaryEducation),
	apprenticeshipEducation_(apprenticeshipEducation),
	secondaryEducation_(secondaryEducation),
	higherEducation_(higherEducation),
	universityEducation_(universityEducation),
	withoutEducation_(withoutEducation),
	unknown_(unknown)
{
}

Education::Education(Education& other):
	withoutCompletedEducation_(other.withoutCompletedEducation_),
	primaryEducation_(other.primaryEducation_),
	apprenticeshipEducation_(other.apprenticeshipEducation_),
	secondaryEducation_(other.secondaryEducation_),
	higherEducation_(other.higherEducation_),
	universityEducation_(other.universityEducation_),
	withoutEducation_(other.withoutEducation_),
	unknown_(other.unknown_)
{
}

Education::~Education()
{
}

int Education::getEducationCount(Enums::EDUCATION_TYPE type)
{
	switch (type)
	{
	case Enums::WITHOUT_COMPLETED:
		return this->withoutCompletedEducation_;
		break;
	case Enums::PRIMARY:
		return this->primaryEducation_;
		break;
	case Enums::APPRENTICESHIP:
		return this->apprenticeshipEducation_;
		break;
	case Enums::SECONDARY:
		return this->secondaryEducation_;
		break;
	case Enums::HIGHER:
		return this->higherEducation_;
		break;
	case Enums::UNIVERSITY:
		return this->universityEducation_;
		break;
	case Enums::WITHOUT_EDUCATION:
		return this->withoutEducation_;
		break;
	case Enums::UNKNOWN:
		return this->unknown_;
		break;
	default:
		return -1;
		break;
	};
}

void Education::addEducationCount(int count, Enums::EDUCATION_TYPE type)
{
	switch (type)
	{
	case Enums::WITHOUT_COMPLETED:
		this->withoutCompletedEducation_ += count;
		break;
	case Enums::PRIMARY:
		this->primaryEducation_ += count;
		break;
	case Enums::APPRENTICESHIP:
		this->apprenticeshipEducation_ += count;
		break;
	case Enums::SECONDARY:
		this->secondaryEducation_ += count;
		break;
	case Enums::HIGHER:
		this->higherEducation_ += count;
		break;
	case Enums::UNIVERSITY:
		this->universityEducation_ += count;
		break;
	case Enums::WITHOUT_EDUCATION:
		this->withoutEducation_ += count;
		break;
	case Enums::UNKNOWN:
		this->unknown_ += count;
		break;
	}
}

Education& Education::operator+=(Education& other)
{
	if (this != &other)
	{
		this->withoutCompletedEducation_ += other.withoutCompletedEducation_;
		this->withoutEducation_ += other.withoutEducation_;
		this->unknown_ += other.unknown_;
		this->secondaryEducation_ += other.secondaryEducation_;
		this->apprenticeshipEducation_ += other.apprenticeshipEducation_;
		this->universityEducation_ += other.universityEducation_;
		this->higherEducation_ += other.higherEducation_;
		this->primaryEducation_ += other.primaryEducation_;
	}
	return *this;
}
