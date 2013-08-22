#include "Field.h"
#include "main.h"

Field::Field(void)
{
}


Field::~Field(void)
{
	//delete[] metrics;
	//delete[] metricsNew;
}

void Field::draw() const
{
	//TODO bug, cant assign a value to lastDraw!
	//if (lastDraw != totalTime)
	{
		apply_surface((int32_t)x - (int32_t)world.player.x + SCREEN_WIDTH/2, (int32_t)y - (int32_t)world.player.y + SCREEN_HEIGHT/2, image, screen);

		//lastDraw = totalTime;
	}
}

void Field::init(const int32_t &x, const int32_t &y, const int32_t &metricsLength)
{
	this->x = (float)x;
	this->y = (float)y;
	
	xGridded = (int32_t)this->x / GRID_SIZE;
	yGridded = (int32_t)this->y / GRID_SIZE;

	grounded = false;

	insertIntoMap(xGridded, yGridded);

	this->metricsLength = metricsLength;
	metrics = new Rect[metricsLength];
	metricsNew = new Rect[metricsLength];
	updateMetrics(metrics, x, y);
}

void Field::updateMetrics(Rect* const &metrics, const int32_t &x, const int32_t &y)
{
	metrics[0].x = x;
	metrics[0].y = y;
	metrics[0].w = GRID_SIZE;
	metrics[0].h = GRID_SIZE;
}

//calls applyCollision then updatePosition
void Field::move(Vector2 &moveVector)
{
	applyCollisionToVector(moveVector);
	updatePosition(x + moveVector.x, y + moveVector.y);
}

//TODO this just is a stub right now, it only sets the vector to 0 on collision
//shortens a movment vector so it only colides, but does not intersect, with other objects
void Field::applyCollisionToVector(Vector2 &moveVector)
{
	int64_t xy64;
	unordered_map<int64_t, FieldBack*>::const_iterator backIt;
	pair<unordered_multimap<int64_t, FieldFront*>::iterator, unordered_multimap<int64_t, FieldFront*>::iterator> frontItPair;
	unordered_multimap<int64_t, FieldFront*>::iterator frontIt;

	int32_t xStart;
	int32_t yStart;
	int32_t xEnd;
	int32_t yEnd;
	int32_t x;
	int32_t y;

	int32_t i;
	int32_t ii;

	updateMetrics(metricsNew, (int32_t)(this->x + moveVector.x), (int32_t)(this->y + moveVector.y));

	for (i = 0; i<metricsLength; i++)
	{
		xStart = metricsNew[i].x / GRID_SIZE;
		if (metricsNew[i].x % GRID_SIZE) xStart--;

		yStart = metricsNew[i].y / GRID_SIZE;
		if (metricsNew[i].y % GRID_SIZE) yStart--;

		xEnd = (metricsNew[i].x + metricsNew[i].w) / GRID_SIZE;
		if ((metricsNew[i].x + metricsNew[i].w) % GRID_SIZE) xEnd++;

		yEnd = (metricsNew[i].y + metricsNew[i].h) / GRID_SIZE;
		if ((metricsNew[i].y + metricsNew[i].h) % GRID_SIZE) yEnd++;

		

		/*
			colidingLayer

			1 colides with 1 and 2 (back back elemente)
			2 colides with 1, 2 and 3 (back elemente)
			3 colides with 2, and 3

			1 and 2 is back map
			3 is front map only
		*/
		for (x = xStart; x <= xEnd; x++)
		{
			for (y = yStart; y <= yEnd; y++)
			{
				xy64 = world.int64FromXY(x, y);

				backIt = world.mapBack.find(xy64);
				if (backIt != world.mapBack.end())
				{
					if (backIt->second != NULL && backIt->second != this && (colidingLayer !=3 || backIt->second->colidingLayer == 2)) //TODO prevent double checking the same object!
					{
						for (ii = 0; ii<backIt->second->metricsLength; ii++)
						{
							if (metricsNew[i].intersectsWith(backIt->second->metrics[ii]))
							{
								if (metricsNew[i].shortenVectorToNotInteresctWith(backIt->second->metrics[ii], moveVector))
								{
									return applyCollisionToVector(moveVector);
								}
								else
								{
									return;
								}
							}
						}
					}
				}

				if (colidingLayer != 1)
				{
					frontItPair = world.mapFront.equal_range(xy64);

					for (frontIt=frontItPair.first; frontIt!=frontItPair.second; ++frontIt)
					{
						if (frontIt->second != NULL && frontIt->second != this) //TODO prevent double checking the same object!
						{
							for (ii = 0; ii<frontIt->second->metricsLength; ii++)
							{
								if (metricsNew[i].intersectsWith(backIt->second->metrics[ii]))
								{
									if (metricsNew[i].shortenVectorToNotInteresctWith(backIt->second->metrics[ii], moveVector))
									{
										return applyCollisionToVector(moveVector);
									}
									else
									{
										return;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

//sets the new positon to the given values, informs all other objects about the collision if needed, updates the grid
void Field::updatePosition(const float &xNew, const float &yNew)
{
	if (x != xNew || y != yNew) {
		updateMetrics(metrics, (int32_t)xNew, (int32_t)yNew);

		applyCollision();

		int32_t newGridX = (int32_t)xNew / GRID_SIZE;
		int32_t newGridY = (int32_t)yNew / GRID_SIZE;

		if (xGridded != newGridX || yGridded != newGridY)
		{
			removeFromMap(xGridded, yGridded);
			insertIntoMap(newGridX, newGridY);
		}

		x = xNew;
		y = yNew;
	
		xGridded = newGridX;
		yGridded = newGridY;
	}
}

//informs every collision that it happened
void Field::applyCollision()
{
	int64_t xy64;
	unordered_map<int64_t, FieldBack*>::const_iterator backIt;
	pair<unordered_multimap<int64_t, FieldFront*>::iterator, unordered_multimap<int64_t, FieldFront*>::iterator> frontItPair;
	unordered_multimap<int64_t, FieldFront*>::iterator frontIt;

	int32_t xStart;
	int32_t yStart;
	int32_t xEnd;
	int32_t yEnd;
	int32_t x;
	int32_t y;

	int32_t i;
	int32_t ii;

	grounded = false;

	for (i = 0; i<metricsLength; i++)
	{
		xStart = metrics[i].x / GRID_SIZE;
		if (metrics[i].x % GRID_SIZE) xStart--;

		yStart = metrics[i].y / GRID_SIZE;
		if (metrics[i].y % GRID_SIZE) yStart--;

		xEnd = (metrics[i].x + metrics[i].w) / GRID_SIZE;
		if ((metrics[i].x + metrics[i].w) % GRID_SIZE) xEnd++;

		yEnd = (metrics[i].y + metrics[i].h) / GRID_SIZE;
		if ((metrics[i].y + metrics[i].h) % GRID_SIZE) yEnd++;

		

		/*
			colidingLayer

			1 colides with 1 and 2 (back back elemente)
			2 colides with 1, 2 and 3 (back elemente)
			3 colides with 2, and 3

			1 and 2 is back map
			3 is front map only
		*/
		for (x = xStart; x <= xEnd; x++)
		{
			for (y = yStart; y <= yEnd; y++)
			{
				xy64 = world.int64FromXY(x, y);

				backIt = world.mapBack.find(xy64);
				if (backIt != world.mapBack.end() && backIt->second != NULL)
				{
					if (backIt->second != this && (colidingLayer !=3 || backIt->second->colidingLayer == 2)) //TODO prevent double checking the same object!
					{
						for (ii = 0; ii<backIt->second->metricsLength; ii++)
						{
							if ( metrics[i].collidesWith(backIt->second->metrics[ii]) )
							{
								if ( !grounded
									&& (metrics[i].y + metrics[i].h) <= (backIt->second->metrics[ii].y)
									&& (metrics[i].x + metrics[i].w) > (backIt->second->metrics[ii].x)
									&& (metrics[i].x) < (backIt->second->metrics[ii].x + backIt->second->metrics[ii].w) )
								{
									if (velocity.y > 0) {
										velocity.y = 0;
									}
									grounded = true;
								}

								backIt->second->onCollision(this);
								break;
							}
						}
					}
				}

				if (colidingLayer != 1)
				{
					frontItPair = world.mapFront.equal_range(xy64);

					for (frontIt=frontItPair.first; frontIt!=frontItPair.second; ++frontIt)
					{
						if (frontIt->second != NULL && frontIt->second != this) //TODO prevent double checking the same object!
						{
							for (ii = 0; ii<frontIt->second->metricsLength; ii++)
							{
								if ( metrics[i].collidesWith(frontIt->second->metrics[ii]) )
								{
									if ( !grounded
										&& (metrics[i].y + metrics[i].h) <= (backIt->second->metrics[ii].y)
										&& (metrics[i].x + metrics[i].w) > (backIt->second->metrics[ii].x)
										&& (metrics[i].x) < (backIt->second->metrics[ii].x + backIt->second->metrics[ii].w) )
									{
										if (velocity.y > 0) {
											velocity.y = 0;
										}
										grounded = true;
									}

									backIt->second->onCollision(this);
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Field::onCollision(const Field* const other)
{

}

void Field::onClick()
{
	
}

void Field::update()
{
	if (lastUpdate != totalTime) {
		lastUpdate = totalTime;

		//REMINDER: THIS HAS TO BE THE VERY LAST THING HAPPENING IN UPDATE!
		//WE MIGHT DO A "delete this" INSIDE myUpdate http://www.parashift.com/c++-faq-lite/delete-this.html
		myUpdate();
	}
}