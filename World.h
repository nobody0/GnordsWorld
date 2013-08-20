#pragma once

#include <unordered_map>
#include "SDL.h"
#include "Field.h"
#include "FieldBack.h"
#include "FieldFront.h"
#include "Player.h"

using namespace std;

class World
{
public:
	World(void);
	virtual ~World(void);
	
	Player player;
	
	unordered_map<int64_t, FieldBack*> mapBack;

	unordered_multimap<int64_t, FieldFront*> mapFront;

	int64_t int64FromXY(const int32_t &x, const int32_t &y);

	void init();

	void generateBack(const int32_t &x, const int32_t &y);
	
	void update();
};

