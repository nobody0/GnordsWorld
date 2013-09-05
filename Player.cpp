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

void Player::init(const int32_t &x, const int32_t &y)
{
	FieldFront::init(x, y);

	image = load_image("Foreground/Gnord/Gnord_still.png");
}

void Player::updateMetrics(Rect* const &metrics, const int32_t &x, const int32_t &y)
{
	metrics[0].x = x;
	metrics[0].y = y;
	metrics[0].w = GRID_SIZE;
	metrics[0].h = GRID_SIZE * 2;
}

void Player::myUpdate()
{
	float speed = 100;
	float jumpHeight = 200;
	float fallSpeed = 500;
	float maxFallSpeed = 600;
	Vector2 moveVector;
	Vector2 moveVectorToApply;

	float maxDelta = 0.05;
	float deltaTimeLeft = deltaTime;
	float myDeltaTime;

	do {
		myDeltaTime = min(maxDelta, deltaTimeLeft);
		deltaTimeLeft -= myDeltaTime;

		if (keystates[SDLK_RIGHT])
		{
			moveVector.x = myDeltaTime * speed;
		}

		if (keystates[SDLK_LEFT])
		{
			moveVector.x = myDeltaTime * -speed;
		}

		if (grounded)
		{
			if (keystates[SDLK_UP])
			{
				velocity.y = -jumpHeight;
				grounded = false;
			}
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