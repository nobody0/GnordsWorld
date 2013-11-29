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
		int32_t drawX = SCREEN_WIDTH/2;
		int32_t drawY = SCREEN_HEIGHT/2;

		if (inventory.actionbar.barObjects[activeAction] != NULL)
		{
			int32_t activeToolOffsetX = 0;
			int32_t activeToolOffsetY = 0;

			switch(armAnimIndex)
			{
			case 0:
				activeToolOffsetX = 4;
				activeToolOffsetY = 14;
				break;
			case 1:
				activeToolOffsetX = 8;
				activeToolOffsetY = 11;
				break;
			case 2:
				activeToolOffsetX = 11;
				activeToolOffsetY = 8;
				break;
			case 3:
				activeToolOffsetX = 11;
				activeToolOffsetY = 5;
				break;
			case 4:
				activeToolOffsetX = 13;
				activeToolOffsetY = -1;
				break;
			case 5:
				activeToolOffsetX = 11;
				activeToolOffsetY = 4;
				break;
			case 6:
				activeToolOffsetX = 12;
				activeToolOffsetY = 8;
				break;
			case 7:
				activeToolOffsetX = 8;
				activeToolOffsetY = 11;
				break;
			}

			if (flip)
			{
				activeToolOffsetX = -activeToolOffsetX;
			}

			//add 16 to x and 32 to y to center it, activeToolOffsetX and activeToolOffsetY are supposed to be how far we ahve to move out of that center
			inventory.actionbar.barObjects[activeAction]->drawActive(drawX + activeToolOffsetX + 16, drawY + activeToolOffsetY + 32);
		}

		if (flip)
		{
			apply_surface(drawX, drawY, bodyFlipped[bodyAnimIndex], screen);
			apply_surface(drawX, drawY, fellFlipped, screen);
			apply_surface(drawX, drawY, armFlipped[armAnimIndex], screen);
		}
		else
		{
			apply_surface(drawX, drawY, body[bodyAnimIndex], screen);
			apply_surface(drawX, drawY, fell, screen);
			apply_surface(drawX, drawY, arm[armAnimIndex], screen);
		}

		lastDraw = totalTime;
	}
}

void Player::init(const int32_t &x, const int32_t &y)
{
	FieldFront::init(x, y, 1, 12);

	activeAction = 0;
	
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

	SDL_PixelFormat* fmt = screen->format;
	Uint32 color = SDL_MapRGBA(fmt, 255, 255, 255, 0);
	light.init(250, color);
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
	float speed = 120;
	float jumpHeight = 210;
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

		if (swimming)
		{
			if (keystates[SDLK_UP] || keystates[SDLK_w] || keystates[SDLK_SPACE])
			{
				velocity.y = -jumpHeight/2;
				grounded = false;
			}
		}
		else
		{
			if (grounded)
			{
				if (keystates[SDLK_UP] || keystates[SDLK_w] || keystates[SDLK_SPACE])
				{
					velocity.y = -jumpHeight;
					grounded = false;
				}
			}
		}

		if (moveVector.x != 0)
		{
			if (grounded && !swimming)
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

		if (mouseDown && mouseDistanceToPlayer <= GRID_SIZE*4)
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

		if (swimming)
		{
			velocity.y += myDeltaTime * fallSpeed/3;
			if (velocity.y > maxFallSpeed/3) velocity.y = maxFallSpeed/3;
		}
		else
		{
			velocity.y += myDeltaTime * fallSpeed;
			if (velocity.y > maxFallSpeed) velocity.y = maxFallSpeed;
		}

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

	light.shine(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}

void Player::useTool(Field* target, const int32_t &x, const int32_t &y)
{
	if (inventory.actionbar.barObjects[activeAction] != NULL)
	{
		inventory.actionbar.barObjects[activeAction]->onUse(target, x, y);
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