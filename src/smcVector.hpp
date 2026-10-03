#pragma once
#include <sstream>
#include <ostream>
#include <stdexcept>

template <typename T>
class smcVector
{
	const unsigned INITIAL_CAPACITY = 10;
	const unsigned CAPACITY_MULTIPLIER = 2;

public:
	// Function: Constructor
	// Purpose: Initializes the ITP vector to have a
	// capacity of INITIAL_CAPACITY and a size of 0.
	// It also dynamically allocates the underlining array data
	// Input: None
	// Returns: Nothing
	smcVector()
	{
		// Capacity set to default of 10
		mCapacity = INITIAL_CAPACITY;
		mSize = 0;
		// Dynamically allocates an array with a capacity of 10
		mArray = new T[mCapacity];
	}

	// Function: Constructor
	// Purpose: Initializes the ITP vector to have a
	// capacity of inputted value.
	// It also dynamically allocates the underlining array data
	// Input: Unsigned integer
	// Returns: Nothing
	smcVector(unsigned inCapacity)
	{
		// Capacity set to input
		mCapacity = inCapacity;
		mSize = 0;
		// Dynamically allocates an array with input capacity
		mArray = new T[mCapacity];
	}

	// Function: Copy Constructor
	// Purpose: Initializes the ITP vector to have a
	// copy of the inputted vector
	// Input: Another smcVector
	// Returns: Nothing
	smcVector(const smcVector<T>& other)
	{
		// 1. Set the new capacity to the other’s size and size = 0
		mCapacity = other.size();
		// 2. Create a new underlying array with the new capacity
		mArray = new T[mCapacity];
		// 3. Iterate over the other vector and push_back items to the new vector
		for (int i = 0; i < other.size(); i++)
		{
			push_back(other[i]);
		}
	}

	// Function: Assignment operator
	// Purpose: Clears the current vector and sets
	// the vector to have a copy of the inputted vector
	// Input: Another smcVector
	// Returns: Nothing
	smcVector<T>& operator=(const smcVector<T>& other)
	{
		// 1. Call the clear function
		clear();
		// 2. Delete the current array
		delete[] mArray;
		// 3. Set the new capacity to the other’s size and size = 0
		mCapacity = other.size();
		mSize = 0;
		// 4. Create a new underlying array with the new capacity
		mArray = new T[mCapacity];
		// 5. Iterate over the other vector and push_back items to the new vector
		for (int i = 0; i < other.size(); i++)
		{
			push_back(other[i]);
		}
		// 6. By convention, operator= returns *this
		return *this;
	}

	// Function: Destructor
	// Purpose: Deletes the underlying array and
	// sets size/capacity to zero
	// Input: None
	// Returns: Nothing
	~smcVector()
	{
		// Deletes underlying array
		delete[] mArray;
		// Sets capacity to 0
		mCapacity = 0;
		// Sets size to 0
		mSize = 0;
	}

	// Function: clear
	// Purpose: Empties the current vector
	// Input: None
	// Returns: None
	void clear()
	{
		// 1. Call delete[] on the underlying array
		delete[] mArray;
		// 2. Create a new underlying array using the old capacity
		mArray = new T[mCapacity];
		// 3. Set size back to 0
		mSize = 0;

	}

	// Function: empty
	// Purpose: Returns true if the vector is empty
	// Input: None
	// Returns: Boolean
	bool empty()
	{
		// Returns true if vector is empty
		if (mSize == 0)
		{
			return true;
		}
		// Returns false if vector is not empty
		else
		{
			return false;
		}
	}

	// Function: capacity
	// Purpose: Returns the current capacity of the underlying array data
	// Input: None
	// Returns: Capacity of underlying array data
	unsigned capacity() const
	{
		return mCapacity;
	}

	// Function: size
	// Purpose: Returns the current size of the vector
	// Input: None
	// Returns: Size of vector
	unsigned size() const
	{
		return mSize;
	}

	// Function: data
	// Purpose: Returns the pointer to the underlying array
	// Input: None
	// Returns: T*
	T* data() const
	{
		return mArray;
	}

	// Function: Subscript operator (read/write version)
	// Purpose: Grabs the specified index from vector
	// Causes an error if the index is out of bounds
	// Input: Index to access
	// Returns: Value at index, by reference
	T& operator[](unsigned index)
	{
		// 1. If index >= size – error!
		if (index >= mSize)
		{
			throw std::out_of_range("The index is out of range");
		}
		// 2. Return the value at the requested index
		return mArray[index];
	}

	// Function: Subscript operator (read-only version)
	// Purpose: Grabs the specified index from vector
	// Causes an error if the index is out of bounds
	// Input: Index to access
	// Returns: Value at index, by reference
	const T& operator[](unsigned index) const
	{
		// 1. If index >= size – error!
		if (index >= mSize)
		{
			throw std::out_of_range("The index is out of range");
		}
		// 2. Return the value at the requested index
		return mArray[index];
	}

	// Function: push_back
	// Purpose: Adds the specified element to the end of the smcVector
	// It automatically reallocates the underlying array if we are
	// going over capacity
	// Input: Value to add (by const reference)
	// Returns: Nothing
	void push_back(const T& value)
	{
		// mArray is not at capacity
		if (mSize < mCapacity)
		{
			// 1. Place the element at index size
			mArray[mSize] = value;
			// 2. Increment size
			mSize++;
		}
		// mArray is at capacity
		else
		{	
			// 1. Increase the capacity (usually double it)
			mCapacity = mCapacity * CAPACITY_MULTIPLIER;
			// 2. Dynamically allocate a new underlying array w/ new capacity
			T* newArray = new T[mCapacity];
			// 3. Copy the data from the old array to the new array
			for (int i = 0; i < mSize; i++)
			{
				newArray[i] = mArray[i];
			}
			// 4. Delete the old array
			delete[] mArray;
			// 5. Set your pointer to the new array
			mArray = newArray;
			// 6. Add an element at index size
			mArray[mSize] = value;
			// 7. Increment size by 1
			mSize++;
		}
	}

	// Function: back
	// Purpose: Returns the current last element in the vector
	// Does not remove this element from the vector
	// Causes an error if there are no elements in the vector
	// Input: Nothing
	// Returns: Value at back of vector, by reference
	T& back()
	{
		// 1. If size == 0 – error!
		if (mSize == 0)
		{
			throw std::out_of_range("Size is zero, cannot return last element");
		}
		// 2. Return the element at size - 1
		return mArray[mSize - 1];
	}

	// Function: pop_back
	// Purpose: Removes the last element from the smcVector
	// Causes an error if there are no elements in the vector
	// Input: Nothing
	// Returns: Nothing
	void pop_back()
	{
		// 1. If size == 0 – error!
		if (mSize == 0)
		{
			throw std::out_of_range("Size is zero, cannot remove last element");
		}
		// 2. Decrement size by 1
		mSize--;
	}

	// Function: Output Stream Operator
	// Purpose: Prints the contents of the vector to the provided stream
	// Written in the format of {x, y, ..., z}
	// Input: Stream to write to, vector to write
	// Output: Stream after values are written
	friend std::ostream& operator<<(std::ostream& os, const smcVector<T>& vector)
	{
		os << "{";
		// Prints all items except for last element
		for (int i = 0; i < vector.size() - 1; i++)
		{
			os << vector[i] << ", ";
		}
		// Prints last element
		os << vector[vector.size()] << "}";
		return os;
	}

private:
	// Holds capacity
	unsigned mCapacity;
	// Holds size
	unsigned mSize;
	// Dynamically allocates underlying array
	T* mArray;
};