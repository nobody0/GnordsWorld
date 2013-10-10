#include "Player.h"
#include "main.h"
#include "Vector2.h"



using namespace std;

Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::draw(bool forceRedraw)
{
	if (forceRedraw)
	{
		if (flip)
		{
			apply_surface((int32_t)x - (int32_t)world.player.x + SCREEN_WIDTH/2, (int32_t)y - (int32_t)world.player.y + SCREEN_HEIGHT/2, bodyFlipped[bodyAnimIndex], screen);
			apply_surface((int32_t)x - (int32_t)world.player.x + SCREEN_WIDTH/2, (int32_t)y - (int32_t)world.player.y + SCREEN_HEIGHT/2, fellFlipped, screen);
			apply_surface((int32_t)x - (int32_t)world.player.x + SCREEN_WIDTH/2, (int32_t)y - (int32_t)world.player.y + SCREEN_HEIGHT/2, armFlipped[armAnimIndex], screen);
		}
		else
		{
			apply_surface((int32_t)x - (int32_t)world.player.x + SCREEN_WIDTH/2, (int32_t)y - (int32_t)world.player.y + SCREEN_HEIGHT/2, body[bodyAnimIndex], screen);
			apply_surface((int32_t)x - (int32_t)world.player.x + SCREEN_WIDTH/2, (int32_t)y - (int32_t)world.player.y + SCREEN_HEIGHT/2, fell, screen);
			apply_surface((int32_t)x - (int32_t)world.player.x + SCREEN_WIDTH/2, (int32_t)y - (int32_t)world.player.y + SCREEN_HEIGHT/2, arm[armAnimIndex], screen);
		}

		lastDraw = totalTime;
	}
}

void Player::init(const int32_t &x, const int32_t &y)
{
	FieldFront::init(x, y, 1, 12);

	activeTool = NULL;
	
	body[0] = load_image("Foreground/Gnord/walk_1.png");
	body[1] = load_image("Foreground/Gnord/walk_2.png");
	body[2] = load_image("Foreground/Gnord/walk_3.png");
	body[3] = load_image("Foreground/Gnord/walk_4.png");
	body[4] = load_image("Foreground/Gnord/walk_5.png");
	body[5] = load_image("Foreground/Gnord/walk_6.png");
	
	fell = load_image("Foreground/Gnord/fell.png");
	
	arm[0] = load_image("Foreground/Gnord/arm_1.png");
	arm[1] = load_image("Foreground/Gnord/arm_2.png");
	arm[2] = load_image("Foreground/Gnord/arm_3.png");
	arm[3] = load_image("Foreground/Gnord/arm_4.png");
	arm[4] = load_image("Foreground/Gnord/arm_5.png");
	arm[5] = load_image("Foreground/Gnord/arm_6.png");
	arm[6] = load_image("Foreground/Gnord/arm_7.png");
	arm[7] = load_image("Foreground/Gnord/arm_8.png");

	
	bodyFlipped[0] = flip_surface(body[0], FLIP_HORIZONTAL);
	bodyFlipped[1] = flip_surface(body[1], FLIP_HORIZONTAL);
	bodyFlipped[2] = flip_surface(body[2], FLIP_HORIZONTAL);
	bodyFlipped[3] = flip_surface(body[3], FLIP_HORIZONTAL);
	bodyFlipped[4] = flip_surface(body[4], FLIP_HORIZONTAL);
	bodyFlipped[5] = flip_surface(body[5], FLIP_HORIZONTAL);

	fellFlipped = flip_surface(fell, FLIP_HORIZONTAL);

	armFlipped[0] = flip_surface(arm[0], FLIP_HORIZONTAL);
	armFlipped[1] = flip_surface(arm[1], FLIP_HORIZONTAL);
	armFlipped[2] = flip_surface(arm[2], FLIP_HORIZONTAL);
	armFlipped[3] = flip_surface(arm[3], FLIP_HORIZONTAL);
	armFlipped[4] = flip_surface(arm[4], FLIP_HORIZONTAL);
	armFlipped[5] = flip_surface(arm[5], FLIP_HORIZONTAL);
	armFlipped[6] = flip_surface(arm[6], FLIP_HORIZONTAL);
	armFlipped[7] = flip_surface(arm[7], FLIP_HORIZONTAL);
	
	bodyAnimStart = -1;
	bodyAnimIndex = 0;

	armAnimStart = -1;
	armAnimIndex = 0;
}


void Player::updateMetrics(Rect* const &metrics, int64_t* const &affectedGrids, const int32_t &x, const int32_t &y)
{
	metrics[0].x = x;
	metrics[0].y = y+8;
	metrics[0].w = 30;
	metrics[0].h = 50;

	int32_t xGridded = (int32_t)floor((double)x / GRID_SIZE);
	int32_t yGridded = (int32_t)floor((double)y / GRID_SIZE);

	affectedGrids[0] = world.int64FromXY(xGridded-1, yGridded-1);
	affectedGrids[1] = world.int64FromXY(xGridded-1, yGridded);
	affectedGrids[2] = world.int64FromXY(xGridded-1, yGridded+1);
	affectedGrids[3] = world.int64FromXY(xGridded-1, yGridded+2);

	affectedGrids[4] = world.int64FromXY(xGridded, yGridded-1);
	affectedGrids[5] = world.int64FromXY(xGridded, yGridded);
	affectedGrids[6] = world.int64FromXY(xGridded, yGridded+1);
	affectedGrids[7] = world.int64FromXY(xGridded, yGridded+2);

	affectedGrids[8] = world.int64FromXY(xGridded+1, yGridded-1);
	affectedGrids[9] = world.int64FromXY(xGridded+1, yGridded);
	affectedGrids[10] = world.int64FromXY(xGridded+1, yGridded+1);
	affectedGrids[11] = world.int64FromXY(xGridded+1, yGridded+2);
}

void Player::myUpdate()
{
	float speed = 100;
	float jumpHeight = 200;
	float fallSpeed = 500;
	float maxFallSpeed = 600;
	Vector2 moveVector;
	Vector2 moveVectorToApply;

	float maxDelta = (float)0.05;
	float deltaTimeLeft = deltaTime;
	float myDeltaTime;

	do {
		myDeltaTime = min(maxDelta, deltaTimeLeft);
		deltaTimeLeft -= myDeltaTime;

		if (keystates[SDLK_RIGHT] || keystates[SDLK_d])
		{
			moveVector.x = myDeltaTime * speed;
		}

		if (keystates[SDLK_LEFT] || keystates[SDLK_a])
		{
			moveVector.x = myDeltaTime * -speed;
		}

		if (grounded)
		{
			if (keystates[SDLK_UP] || keystates[SDLK_w] || keystates[SDLK_SPACE])
			{
				velocity.y = -jumpHeight;
				grounded = false;
			}
		}

		if (moveVector.x != 0)
		{
			if (grounded)
			{
				if (bodyAnimStart == -1)
				{
					bodyAnimStart = totalTime;
				}

				float animSpeed = 10/speed;
				int32_t size = sizeof(body) / sizeof(body[0]);
				int32_t offset = (int32_t)((totalTime-bodyAnimStart)/animSpeed);

				bodyAnimIndex = offset % size;
			}

			if (moveVector.x > 0)
			{
				flip = false;
			}
			else
			{
				flip = true;
			}
		}
		else
		{
			bodyAnimIndex = 0;
			bodyAnimStart = -1;
		}

		if (mouseDown)
		{
			if (armAnimStart == -1)
			{
				armAnimStart = totalTime;
			}

			float animSpeed = (float)0.1;
			int32_t size = sizeof(arm) / sizeof(arm[0]);
			int32_t offset = (int32_t)ceil((totalTime-armAnimStart)/animSpeed);

			armAnimIndex = offset % size;
		}
		else
		{
			armAnimIndex = 0;
			armAnimStart = -1;
		}
		velocity.y += myDeltaTime * fallSpeed;
		if (velocity.y > maxFallSpeed) velocity.y = maxFallSpeed;

		if (velocity.y != 0)
		{
			moveVectorToApply.x = 0;
			moveVectorToApply.y = velocity.y * myDeltaTime;
			move(moveVectorToApply);
			velocity.y = moveVectorToApply.y / myDeltaTime;
		}

		if (velocity.x != 0)
		{
			moveVectorToApply.x = velocity.x * myDeltaTime;
			moveVectorToApply.y = 0;
			move(moveVectorToApply);
			velocity.x = moveVectorToApply.x / myDeltaTime;
		}

		if (moveVector.y != 0)
		{
			moveVectorToApply.x = 0;
			moveVectorToApply.y = moveVector.y;
			move(moveVectorToApply);
			moveVector.y = moveVectorToApply.y;
		}

		if (moveVector.x != 0)
		{
			moveVectorToApply.x = moveVector.x;
			moveVectorToApply.y = 0;
			move(moveVectorToApply);
			moveVector.x = moveVectorToApply.x;
		}
	} while (deltaTimeLeft > 0);
}

void Player::shine()
{
	if (lastShine == totalTime) {
		return;
	}

	lastShine = totalTime;

	SDL_PixelFormat* fmt = screen->format;
	Uint32 shade = SDL_MapRGBA(fmt, 255, 255, 255, 0);
	Uint32 shade2 = SDL_MapRGBA(fmt, 32, 32, 32, 0);

	int xStart = SCREEN_WIDTH/2 - 200;
	int xEnd = xStart + 400;
	int yStart = SCREEN_HEIGHT/2- 200;
	int yEnd = yStart + 400;

	Uint32* lightPixels = (Uint32*)lightScreen->pixels;

	int x, y;
	Uint32* offsetPixel = NULL;
	Uint32* offsetMap = NULL;
	for (x = xStart; x < xEnd; x++)
	{
		offsetPixel = lightPixels + yStart * SCREEN_WIDTH + x;
		offsetMap = lightMap + yStart * SCREEN_WIDTH + x;

		for (y = yStart; y < yEnd; y++)
		{
			offsetPixel += SCREEN_WIDTH;
			offsetMap += SCREEN_WIDTH;

			if ((*offsetPixel) == 0)
			{
				(*offsetMap) = shade;
			}
			else
			{
				(*offsetMap) = shade2;
			}
		}
	}
}

void Player::useTool(Field* target, const int32_t &x, const int32_t &y)
{
	if (activeTool != NULL)
	{
		activeTool->onUse(target, x, y);
	}
	else
	{
		defaultTool.onUse(target, x, y);
	}
}

void Player::onUsed(const ToolTypes &toolType, const int32_t &toolLevel)
{
	if (toolType == Enemy)
	{
		health -= toolLevel*deltaTime;
	}

	if (health <= 0)
	{
		/*
		removeFromMap();

		delete this;
		return;
		*/
	}
}