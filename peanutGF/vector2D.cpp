#include "vector2D.h"
#include <fstream>

namespace pnGF{
	std::ostream& operator<<(std::ostream& os, const Vector2D& rhs)
	{
		os << " " << rhs.x << " " << rhs.y;

		return os;
	}


	std::ifstream& operator>>(std::ifstream& is, Vector2D& lhs)
	{
		is >> lhs.x >> lhs.y;

		return is;
	}
}