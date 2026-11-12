#pragma once

/*
	ÅV‚Æ‰ß‹‚Ì’l‚ğ‚Â‚½‚ß‚Ì\‘¢‘Ì
	ˆ»•”
*/

template <typename T>
struct DataOfChange
{
	T current;
	T last;
};

template <>
struct DataOfChange<bool>
{
	bool current;
	bool last;
	DataOfChange() : current(false), last(false) {}
};