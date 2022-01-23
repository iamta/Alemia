#pragma once
// Interface for all drawable objects
class IDrawable
{
public :
	// Draw the object at specific coordinates on the Console Handle
	virtual void Draw(int x1, int y1, int x2, int y2, bool DrawRect) = 0;

	virtual void Clear() = 0 ;
};

