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

	image = SURFACE_PLAYER;

	state = CreatureStates::Idle;
}

void Player::myUpdate()
{
	switch (state)
	{
		case CreatureStates::Jumping :
		case CreatureStates::Walking :
		case CreatureStates::Idle :
		default :
			float speed = 60;
			Vector2 moveVector;

			if (keystates[SDLK_RIGHT])
				moveVector.x = deltaTime * speed;

			if (keystates[SDLK_LEFT])
				moveVector.x = -deltaTime * speed;

			if (keystates[SDLK_DOWN])
				moveVector.y = deltaTime * speed;

			if (keystates[SDLK_UP])
				moveVector.y = -deltaTime * speed;

			if (moveVector.x != 0 || moveVector.y != 0)
			{
				move(moveVector);
			}

			break;
	}
}