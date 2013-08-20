#pragma once

#include "SDL.h"
#include "Rect.h"
#include "Vector2.h"

class Field
{
public:
	Field(void);
	virtual ~Field(void);

	//never ever write these two directly, use updatePosition instead !
	float x;
	float y;
	int32_t xGridded;
	int32_t yGridded;

	float lastDraw;
	
	//TODO metrics
	int32_t metricsLength;
	
	Rect* metrics;

	Rect* metricsNew;

	/*
		1 colides with 1 and 2 (back back elemente)
		2 colides with 1, 2 and 3 (back elemente)
		3 colides with 2, and 3
	*/
	int32_t colidingLayer;


	bool visible;

	void draw() const;

	virtual void init(const int32_t &x, const int32_t &y, const int32_t &metricsLength = 1);
	
	virtual void updateMetrics(Rect* const &metrics, const int32_t &x, const int32_t &y);

	void move(Vector2 &moveVector);

	void applyCollisionToVector(Vector2 &moveVector);

	void applyCollision() const;

	void updatePosition(const float &xNew, const float &yNew);

	void onCollision(const Field* const other);

	void update();

	virtual void removeFromMap(const int32_t &x, const int32_t &y) const = 0;
	virtual void insertIntoMap(const int32_t &x, const int32_t &y) const = 0;

protected:
	SDL_Surface* image;

	float lastUpdate;

	virtual void myUpdate() = 0;
};

