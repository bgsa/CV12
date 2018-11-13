#pragma once

template <typename T>
class IEquatable {
public:

	virtual bool equals(T* other) 
	{
		return this == other;
	}

};
