#include "FieldBackIron.h"
#include "main.h"


FieldBackIron::FieldBackIron(void)
{
}

FieldBackIron::~FieldBackIron(void)
{
}

void FieldBackIron::init(const int32_t &x, const int32_t &y)
{
	FieldBack::init(x, y);

	switch (myRand(x ^ (y<<2)) % 6)
	{
	case 0:
		image = load_image("Background/Erze/Eisen/Eisen01.png");
		break;
	case 1:
		image = load_image("Background/Erze/Eisen/Eisen02.png");
		break;
	case 2:
		image = load_image("Background/Erze/Eisen/Eisen03.png");
		break;
	case 3:
		image = load_image("Background/Erze/Eisen/Eisen04.png");
		break;
	case 4:
		image = load_image("Background/Erze/Eisen/Eisen05.png");
		break;
	case 5:
		image = load_image("Background/Erze/Eisen/Eisen06.png");
		break;
	}
}

void FieldBackIron::myUpdate()
{

}