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
		image = load_image("erz_gras1.jpg");
		break;
	case 1:
		image = load_image("erz_gras2.jpg");
		break;
	case 2:
		image = load_image("erz_gras3.jpg");
		break;
	case 3:
		image = load_image("erz_gras4.jpg");
		break;
	case 4:
		image = load_image("erz_gras5.jpg");
		break;
	case 5:
		image = load_image("erz_gras6.jpg");
		break;
	}
}

void FieldBackGrass::myUpdate()
{

}