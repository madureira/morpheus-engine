#pragma once

#include <locale>
#include <sstream>

namespace Morpheus {

	struct NumberFormatter : std::numpunct<char>
	{
		// use . as separator
		char do_thousands_sep() const
		{
			return '.';
		}

		// digits are grouped by 3
		std::string do_grouping() const
		{
			return "\3";
		}
	};

	class NumberUtil
	{
	public:
		static std::string FormatThousandSeparator(int number)
		{
			std::locale loc(std::locale(std::locale(), new NumberFormatter));
			std::stringstream ss;
			ss.imbue(loc);
			ss << number;

			return ss.str();
		}
	};

}
