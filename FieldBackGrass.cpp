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
		image = load_image("Background/Erze/Grass/Grass01.png");
		break;
	case 1:
		image = load_image("Background/Erze/Grass/Grass02.png");
		break;
	case 2:
		image = load_image("Background/Erze/Grass/Grass03.png");
		break;
	case 3:
		image = load_image("Background/Erze/Grass/Grass04.png");
		break;
	case 4:
		image = load_image("Background/Erze/Grass/Grass05.png");
		break;
	case 5:
		image = load_image("Background/Erze/Grass/Grass06.png");
		break;
	}
}

void FieldBackGrass::myUpdate()
{

}