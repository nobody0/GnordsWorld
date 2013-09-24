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

void Field::draw(bool forceRedraw)
{
	if (lastDraw != totalTime && !forceRedraw)
	{
		apply_surface((int32_t)x - (int32_t)world.player.x + SCREEN_WIDTH/2, (int32_t)y - (int32_t)world.player.y + SCREEN_HEIGHT/2, image, screen);

		lastDraw = totalTime;
	}
}

void Field::init(const int32_t &x, const int32_t &y, const int32_t &metricsLength, const int32_t &affectedGridsLength)
{
	this->x = (float)x;
	this->y = (float)y;
	
	xGridded = (int32_t)floor(this->x / GRID_SIZE);
	yGridded = (int32_t)floor(this->y / GRID_SIZE);

	grounded = false;

	this->metricsLength = metricsLength;
	metrics = new Rect[metricsLength];
	metricsNew = new Rect[metricsLength];

	this->affectedGridsLength = affectedGridsLength;
	affectedGrids = new int64_t[affectedGridsLength];
	affectedGridsNew = new int64_t[affectedGridsLength];

	updateMetrics(metrics, affectedGrids, x, y);

	insertIntoMap();
	
	appropriateTool = Default;
	health = (float)1.1;
}

void Field::updateMetrics(Rect* const &metrics, int64_t* const &affectedGrids, const int32_t &x, const int32_t &y)
{
	metrics[0].x = x;
	metrics[0].y = y;
	metrics[0].w = GRID_SIZE;
	metrics[0].h = GRID_SIZE;
	
	int32_t xGridded = (int32_t)floor((double)x / GRID_SIZE);
	int32_t yGridded = (int32_t)floor((double)y / GRID_SIZE);
	affectedGrids[0] = world.int64FromXY(xGridded, yGridded);
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

	int32_t i;
	int32_t ii;
	int32_t ai;

	updateMetrics(metricsNew, affectedGridsNew, (int32_t)(this->x + moveVector.x), (int32_t)(this->y + moveVector.y));

	for (ai = 0; ai<affectedGridsLength; ai++)
	{
		xy64 = affectedGridsNew[ai];

		backIt = world.mapBack.find(xy64);
		if (backIt != world.mapBack.end())
		{
			if (backIt->second != NULL && backIt->second != this && (colidingLayer !=3 || backIt->second->colidingLayer == 2)) //TODO prevent double checking the same object!
			{
				for (i = 0; i<metricsLength; i++)
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
		}

		if (colidingLayer != 1)
		{
			frontItPair = world.mapFront.equal_range(xy64);

			for (frontIt=frontItPair.first; frontIt!=frontItPair.second; ++frontIt)
			{
				if (frontIt->second != NULL && frontIt->second != this) //TODO prevent double checking the same object!
				{
					for (i = 0; i<metricsLength; i++)
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

//sets the new positon to the given values, informs all other objects about the collision if needed, updates the grid
void Field::updatePosition(const float &xNew, const float &yNew)
{
	if (x != xNew || y != yNew) {
		updateMetrics(metrics, affectedGrids, (int32_t)xNew, (int32_t)yNew);

		applyCollision();

		int32_t newGridX = (int32_t)floor(xNew / GRID_SIZE);
		int32_t newGridY = (int32_t)floor(yNew / GRID_SIZE);

		if (xGridded != newGridX || yGridded != newGridY)
		{
			removeFromMap();

			x = xNew;
			y = yNew;
	
			xGridded = newGridX;
			yGridded = newGridY;

			insertIntoMap();
		}
		else
		{
			x = xNew;
			y = yNew;
	
			xGridded = newGridX;
			yGridded = newGridY;
		}
	}
}

//informs every collision that it happened
void Field::applyCollision()
{
	int64_t xy64;
	unordered_map<int64_t, FieldBack*>::const_iterator backIt;
	pair<unordered_multimap<int64_t, FieldFront*>::iterator, unordered_multimap<int64_t, FieldFront*>::iterator> frontItPair;
	unordered_multimap<int64_t, FieldFront*>::iterator frontIt;

	int32_t i;
	int32_t ii;
	int32_t ai;

	grounded = false;

	for (ai = 0; ai<affectedGridsLength; ai++)
	{
		xy64 = affectedGrids[ai];

		backIt = world.mapBack.find(xy64);
		if (backIt != world.mapBack.end() && backIt->second != NULL)
		{
			if (backIt->second != this && (colidingLayer !=3 || backIt->second->colidingLayer == 2)) //TODO prevent double checking the same object!
			{
				for (i = 0; i<metricsLength; i++)
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
		}

		if (colidingLayer != 1)
		{
			frontItPair = world.mapFront.equal_range(xy64);

			for (frontIt=frontItPair.first; frontIt!=frontItPair.second; ++frontIt)
			{
				if (frontIt->second != NULL && frontIt->second != this) //TODO prevent double checking the same object!
				{
					for (i = 0; i<metricsLength; i++)
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

void Field::onCollision(const Field* const other)
{

}

void Field::onUsed(const ToolTypes &toolType, const int32_t &toolLevel)
{
	if (toolType == appropriateTool)
	{
		health -= 2*toolLevel*deltaTime;
	}
	else
	{
		health -= toolLevel*deltaTime;
	}

	if (health <= 0)
	{
		removeFromMap();

		delete this;
		return;
	}
}

void Field::update()
{
	if (lastUpdate != totalTime) {
		lastUpdate = totalTime;

		myUpdate();
	}
}