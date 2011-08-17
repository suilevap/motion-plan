#include "gtest/gtest.h"
#include "RayCast.h"
#include "vector"


class RayCastVector: public RayCast
{
public:
	std::vector<std::pair<int,int>> Points;

	virtual bool HandlePoint(int x, int y)
	{
		Points.push_back(std::pair<int,int>(x,y));
		return false;
	}
};

TEST(RayCastTest, Lines)
{
	RayCastVector* rayCastVector  = new RayCastVector();
	rayCastVector->Execute(0,0, 10, 5);
	EXPECT_EQ(11, rayCastVector->Points.size());
	delete rayCastVector;
}
