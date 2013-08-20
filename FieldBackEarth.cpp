#include "FieldBackEarth.h"
#include "main.h"
#include "FieldBackGrass.h"


FieldBackEarth::FieldBackEarth(void)
{
}


FieldBackEarth::~FieldBackEarth(void)
{
}

void FieldBackEarth::init(const int32_t &x, const int32_t &y)
{
	FieldBack::init(x, y);

	switch (myRand(x ^ (y<<2)) % 6)
	{
	case 0:
		image = SURFACE_ERDE_1;
		break;
	case 1:
		image = SURFACE_ERDE_2;
		break;
	case 2:
		image = SURFACE_ERDE_3;
		break;
	case 3:
		image = SURFACE_ERDE_4;
		break;
	case 4:
		image = SURFACE_ERDE_5;
		break;
	case 5:
		image = SURFACE_ERDE_6;
		break;
	}
}

void FieldBackEarth::myUpdate()
{
	if (updateCounter > 10) {
		unordered_map<int64_t, FieldBack*>::iterator backIt = world.mapBack.find(world.int64FromXY(xGridded, yGridded-1));
		if (backIt != world.mapBack.end())
		{
			if (backIt->second == NULL)
			{
				removeFromMap(xGridded, yGridded);

				FieldBackGrass* fieldBackGrass = new FieldBackGrass();
				fieldBackGrass->init(xGridded*GRID_SIZE, yGridded*GRID_SIZE);

				//reminder: this has to be the very last thing to execute!
				delete this;
				return;
			}
		}

		updateCounter = 0;
	} else {
		updateCounter++;
	}
}