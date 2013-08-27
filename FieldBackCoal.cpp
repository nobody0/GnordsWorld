#include "FieldBackCoal.h"
#include "main.h"


FieldBackCoal::FieldBackCoal(void)
{
}

FieldBackCoal::~FieldBackCoal(void)
{
}

void FieldBackCoal::init(const int32_t &x, const int32_t &y)
{
	FieldBack::init(x, y);

	switch (myRand(x ^ (y<<2)) % 6)
	{
	case 0:
		image = load_image("Background/Erze/Kohle/Kohle01.png");
		break;
	case 1:
		image = load_image("Background/Erze/Kohle/Kohle02.png");
		break;
	case 2:
		image = load_image("Background/Erze/Kohle/Kohle03.png");
		break;
	case 3:
		image = load_image("Background/Erze/Kohle/Kohle04.png");
		break;
	case 4:
		image = load_image("Background/Erze/Kohle/Kohle05.png");
		break;
	case 5:
		image = load_image("Background/Erze/Kohle/Kohle06.png");
		break;
	}
}

void FieldBackCoal::myUpdate()
{

}