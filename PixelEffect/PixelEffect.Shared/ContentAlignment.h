#pragma once

enum class VerticalAlignment 
{
	LEFT = 1,
	CENTER = 2,
	RIGHT = 3,
	NONE = 4
};

enum class HorizontalAlignment 
{
	TOP = 1,
	MIDDLE = 2,
	BOTTOM = 3,
	NONE = 4
};

class ContentAlignment 
{
public:
	VerticalAlignment vertical;
	HorizontalAlignment horizontal;

	ContentAlignment() 
	{
		vertical = VerticalAlignment::NONE;
		horizontal = HorizontalAlignment::NONE;
	}

	ContentAlignment(VerticalAlignment verticalAlignment, HorizontalAlignment horizontalAlignment) 
	{
		vertical = verticalAlignment;
		horizontal = horizontalAlignment;
	}
};