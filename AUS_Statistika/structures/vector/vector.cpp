#include "vector.h"
#include "../utils.h"
#include <cstdlib>
#include <cstring>

namespace structures
{
	Vector::Vector(size_t size) :
		memory_(std::calloc(size, 1)),
		size_(size)
	{	
	}

	Vector::Vector(Vector& other) :
		Vector(other.size_)
	{
		//Done 01: Vector::Vector
		std::memcpy(this->memory_, other.memory_, this->size_);
	}

	Vector::~Vector()
	{
		//Done 01: Vector::~Vector
		std::free(this->memory_); // pre CALLOC pouzit FREE, pre NEW pouzit DELETE
		this->memory_ = nullptr;
		this->size_ = 0;
	}

	size_t Vector::size()
	{
		return size_;
	}

	Structure& Vector::assign(Structure& other)
	{
		//Done 01: Vector::assign
		if (this != &other)
		{
			Vector& otherVector = dynamic_cast<Vector&>(other);
			this->memory_ = std::realloc(this->memory_, otherVector.size_);
			std::memcpy(this->memory_, otherVector.memory_, otherVector.size_);
			this->size_ = otherVector.size_;
		}
		return *this;
	}

	bool Vector::equals(Structure& other)
	{
		//Done 01: Vector::equals
		Vector* otherVector = dynamic_cast<Vector*>(&other);
		if (otherVector == nullptr)
		{
			return false;
		}
		return this->size_ == otherVector->size_ &&
			std::memcmp(this->memory_, otherVector->memory_, this->size_) == 0;
	}

	byte& Vector::operator[](int index)
	{
		return at(index);
	}

	byte& Vector::at(int index)
	{
		//Done 01: Vector::at
		return *this->getBytePointer(index);
	}

	void Vector::copy(Vector& src, int srcStartIndex, Vector& dest, int destStartIndex, int length)
	{
		//Done 01: Vector::copy
		if (length > 0)
		{
			if (srcStartIndex < 0 || srcStartIndex + length - 1 >= src.size_)
			{
				throw std::out_of_range("Vector::copy: Invalid index in src vector");
			}
			if (destStartIndex < 0 || destStartIndex + length - 1 >= dest.size_)
			{
				throw std::out_of_range("Vector::copy: Invalid index in dest vector");
			}
			if (&src != &dest || 
				srcStartIndex >= destStartIndex + length || 
				destStartIndex >= srcStartIndex + length)
			{
				std::memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
			}
			else
			{
				std::memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
			}
		}
	}

	byte* Vector::getBytePointer(int index)
	{
		//Done 01: Vector::getBytePointer
		if (index < 0 || index >= this->size_)
		{
			throw std::out_of_range("Vector::getBytePointer: invalid index.");
		}
		return reinterpret_cast<byte*>(this->memory_) + index; //reinterpret_cast na pretypovanie pointrov
	}
}