#include "age.h"

Age::Age():
    men_(new structures::Array<int>(101)),
    women_(new structures::Array<int>(101))
{
}

Age::~Age()
{
    delete this->men_;
    delete this->women_;

    this->men_ = nullptr;
    this->women_ = nullptr;
}

void Age::addAge(Enums::GENDER gender, structures::Array<int>& ages)
{
    structures::Array<int>& thisArray = getAllAges(gender);
    if (thisArray.size() != ages.size())
    {
        throw std::logic_error("Age::addAge: Arrays have different size");
    }
    for (int i = 0; i < static_cast<int>(thisArray.size()); i++)
    {
        thisArray.at(i) += ages[i];
    }
}

int Age::getAgeCount(Enums::GENDER gender, int ageCategory)
{
    int value = 0;
    switch (gender)
    {
    case Enums::MEN:
        value = this->men_->at(ageCategory);
        break;
    case Enums::WOMEN:
        value = this->women_->at(ageCategory);
        break;
    case Enums::UNSPECIFIED_GENDER:
        value = this->men_->at(ageCategory) + this->women_->at(ageCategory);
        break;
    }
    return value;
}

int Age::getEconomicAgeCount(Enums::GENDER gender, Enums::ECONOMIC_AGE_GROUP ageGroup)
{
    int startIndex = 0;
    int endIndex = 0;
    int result = 0;
    switch (ageGroup)
    {
    case Enums::PRE_PRODUCTIVE:
        startIndex = 0;
        endIndex = 14;
        break;
    case Enums::PRODUCTIVE:
        startIndex = 15;
        endIndex = 64;
        break;
    case Enums::POST_PRODUCTIVE:
        startIndex = 65;
        endIndex = 100;
        break;
    default:
        startIndex = 0;
        endIndex = 100;
        break;
    }
    for (int i = startIndex; i <= endIndex; i++)
    {
        switch (gender)
        {
        case Enums::MEN:
            result += this->men_->at(i);
            break;
        case Enums::WOMEN:
            result += this->women_->at(i);
            break;
        default:
            result += this->men_->at(i) + this->women_->at(i);
            break;
        }
    }
    return result;
}

structures::Array<int>& Age::getAllAges(Enums::GENDER gender)
{
    switch (gender)
    {
    case Enums::MEN:
        return *this->men_;
        break;
    case Enums::WOMEN:
        return *this->women_;
        break;
    default:
        throw std::logic_error("Age::getAllAges: Cannot get unspecified ages.");
        break;
    }
}

Age& Age::operator+=(Age& other)
{
    this->addAge(Enums::MEN, other.getAllAges(Enums::MEN));
    this->addAge(Enums::WOMEN, other.getAllAges(Enums::WOMEN));
    return *this;
}
