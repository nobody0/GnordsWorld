#include "FieldBackGrass.h"
#include "main.h"


FieldBackGrass::FieldBackGrass(void)
{
}


FieldBackGrass::~FieldBackGrass(void)
{
}

void FieldBackGrass::init(const int32_t &x, const int32_t &y)
{
	FieldBack::init(x, y);

	switch (myRand(x ^ (y<<2)) % 6)
	{
	case 0:
		image = SURFACE_GRAS_1;
		break;
	case 1:
		image = SURFACE_GRAS_2;
		break;
	case 2:
		image = SURFACE_GRAS_3;
		break;
	case 3:
		image = SURFACE_GRAS_4;
		break;
	case 4:
		image = SURFACE_GRAS_5;
		break;
	case 5:
		image = SURFACE_GRAS_6;
		break;
	}
}

void FieldBackGrass::myUpdate()
{

}