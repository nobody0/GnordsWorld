#pragma once

#include "Rect.h"
#include "Vector2.h"
#include "ToolTypes.h"

class Field
{
public:
	Field(void);
	virtual ~Field(void);

	float x;
	float y;
	int32_t xGridded;
	int32_t yGridded;

	Vector2 velocity;
	
	bool liquid;

	bool grounded;
	bool swimming;
	
	int32_t metricsLength;
	int32_t affectedGridsLength;

	Rect* metrics;
	int64_t* affectedGrids;

	Rect* metricsNew;
	int64_t* affectedGridsNew;

	/*
		1 colides with 1 and 2 (back back elemente)
		2 colides with 1, 2 and 3 (back elemente)
		3 colides with 2, and 3
	*/
	int32_t colidingLayer;
	
	ToolTypes appropriateTool;
	float health;


	bool visible;

	virtual void draw(bool forceRedraw = false);

	virtual void init(const int32_t &x, const int32_t &y, const int32_t &metricsLength = 1, const int32_t &affectedGridsLength = 1);
	
	virtual void updateMetrics(Rect* const &metrics, int64_t* const &affectedGrids, const int32_t &x, const int32_t &y);
	
	void move(Vector2 &moveVector);

	void applyCollisionToVector(Vector2 &moveVector);

	void applyCollision();

	void updatePosition(const float &xNew, const float &yNew);

	void onCollision(const Field* const other);

	virtual void onUsed(const ToolTypes &toolType, const int32_t &toolLevel);

	void update();

	virtual void shine();

	virtual void removeFromMap() const = 0;
	virtual void insertIntoMap() const = 0;

protected:
	SDL_Surface* image;

	float lastUpdate;
	float lastDraw;

	virtual void myUpdate() = 0;
};

