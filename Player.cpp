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

	image = load_image("Gnord_still.png");
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
		float speed = 90;
		float jumpHeight = 8;
		float fallSpeed = 15;
		float maxFallSpeed = 20;
		Vector2 moveVector;
		Vector2 moveVectorToApply;

		if (keystates[SDLK_RIGHT])
		{
			moveVector.x = deltaTime * speed;
		}

		if (keystates[SDLK_LEFT])
		{
			moveVector.x = -deltaTime * speed;
		}

		if (grounded)
		{
			if (keystates[SDLK_UP])
			{
				velocity.y = -jumpHeight;
				grounded = false;
			}
		}
			
		if (!grounded || moveVector.x)
		{
			velocity.y += deltaTime * fallSpeed;
			if (velocity.y > maxFallSpeed) velocity.y = maxFallSpeed;
		}
			
		moveVector += velocity;

		if (moveVector.y != 0)
		{
			moveVectorToApply.x = 0;
			moveVectorToApply.y = moveVector.y;
			move(moveVectorToApply);
		}

		if (moveVector.x != 0)
		{
			moveVectorToApply.x = moveVector.x;
			moveVectorToApply.y = 0;
			move(moveVectorToApply);
		}
}