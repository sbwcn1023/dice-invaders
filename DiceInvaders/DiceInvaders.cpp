#include <windows.h>
#include <cassert>
#include "DiceInvaders.h"

#include "Model\Items.h"
#include "Model\Bombs.h"
#include "Model\Enemies.h"
#include "Model\Players.h"
#include "Model\Rockets.h"

#include "Service\CollisionDetector.h"
#include "Service\EnemyFactory.h"

#include <vector>
using namespace std;

class DiceInvadersLib
{
public:
	explicit DiceInvadersLib(const char* libraryPath)
	{
		m_lib = LoadLibrary(libraryPath);
		assert(m_lib);

		DiceInvadersFactoryType* factory = (DiceInvadersFactoryType*)GetProcAddress(
				m_lib, "DiceInvadersFactory");
		m_interface = factory();
		assert(m_interface);
	}

	~DiceInvadersLib()
	{
		FreeLibrary(m_lib);
	}

	IDiceInvaders* get() const 
	{
		return m_interface;
	}

private: 
	DiceInvadersLib(const DiceInvadersLib&);
	DiceInvadersLib& operator=(const DiceInvadersLib&);

private: 
	IDiceInvaders* m_interface;
	HMODULE m_lib;
};


int APIENTRY WinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	LPSTR commandLine,
	int commandShow)
{



	/*
	 * Inline configuration/setup.
	 */

	DiceInvadersLib lib("DiceInvaders.dll");
	IDiceInvaders* system = lib.get();

	system->init(640, 480);

	float playerStartPosition = 320;
	int playerScore = 0;
	int playerLives = 3;
	int positionLimitLeft = 1;
	int positionLimitRight = 606;
	float lastTime = system->getElapsedTime();
	CollisionDetector cd = CollisionDetector();



	/*
	 * Sprites.
	 * Instantiated once as they can be drawn in different places simultaneously.
	 */

	// Player.
	ISprite* playerSprite = system->createSprite("data/player.bmp");
	ISprite* rocketSprite = system->createSprite("data/rocket.bmp");

	// Enemy.
	ISprite* enemySprite1 = system->createSprite("data/enemy1.bmp");
	ISprite* enemySprite2 = system->createSprite("data/enemy2.bmp");
	ISprite* bombSprite = system->createSprite("data/bomb.bmp");

	Players players;
	Rockets rockets = Rockets();

	

	/*
	 * Enemies.
	 */

	EnemyFactory ef = EnemyFactory();
	Enemies enemies;
	Bombs bombs;

	

	/*
	 * The game loop.
	 */
	while (system->update())
	{
		
		
		
		/*
		 * Meta stuff.
		 */
		float newTime = system->getElapsedTime();
		float move = (newTime - lastTime) * 160.0f;
		lastTime = newTime;

		// Elapsed time.
		char elapsedTimeText[80];
		char elapsedTime [5];
		itoa(int(newTime), elapsedTime, 10);
		strcpy (elapsedTimeText,"Time: ");
		strcat (elapsedTimeText,elapsedTime);
		strcat (elapsedTimeText," s");
		system->drawText(50, 300, elapsedTimeText);
		
		// Lives left.
		char livesText[80];
		char lives [5];
		itoa(playerLives, lives, 10);
		strcpy (livesText,"Lives: ");
		strcat (livesText,lives);
		system->drawText(50, 316, livesText);

		// Player score.
		char scoreText[80];
		char score [5];
		itoa(playerScore, score, 10);
		strcpy (scoreText,"Score: ");
		strcat (scoreText,score);
		system->drawText(50, 332, scoreText);
		
		

		/*
		 * Game condition.
		 */
		
		if (playerLives == 0 || enemies.FarDown() >= 448)
		{
			system->drawText(274, 300, "You lose! :-(");
			system->drawText(254, 316, "Press alt+x to quit.");
			continue;
		}
		
		
		
		/*
		 * Player.
		 */

		IDiceInvaders::KeyStatus keys;
		system->getKeyStatus(keys);
		
		if (playerLives >= 0 && !players.Any())
		{
			players.Add(playerStartPosition);
		}

		if (keys.right && players.Position[0] < positionLimitRight)
			players.Right(move);
		else if (keys.left && players.Altitude[0] > positionLimitLeft)
			players.Left(move);

		playerSprite->draw(int(players.Position[0]), players.Altitude[0]);
		playerStartPosition = players.Position[0];



		/*
		 * Enemies.
		 */
		
		if (!enemies.Any())
			ef.GenerateEnemies(&enemies);

		if (enemies.FarLeft() < positionLimitLeft)
			enemies.Right();

		if (enemies.FarRight() > positionLimitRight)
			enemies.Left();

		enemies.Step(move);

		for (int i = enemies.Position.size() - 1; i >= 0; --i)
		{
			srand(unsigned(newTime * 500000 * i*i*i));
			int random_integer;
			random_integer = 1+int(10*rand()/(RAND_MAX + 1.0));

			if (random_integer == 7)
			{
				enemies.Drop(&bombs, i);
			}

			enemySprite1->draw(enemies.Position[i], enemies.Altitude[i]);
		}



		/*
		 * Bombs.
		 */

		if (bombs.Any())
			bombs.Fall(move);

		for(int i = bombs.Count() - 1; i >= 0; --i)
			bombSprite->draw(bombs.Position[i], bombs.Altitude[i]);
		


		/*
		 * Love and Rocket.
		 */

		if (keys.fire && !rockets.Any())
			players.Fire(&rockets);

		rockets.Step(move);
		
		if (rockets.Any())
			rocketSprite->draw(int(rockets.Position.front()), rockets.Altitude.front());



		/*
		 * Collisions.
		 */
		
		if (cd.ResolveCollisions(&enemies, &rockets))
			playerScore++;

		if (cd.ResolveCollisions(&enemies, &players))
			playerLives--;

		if (cd.ResolveCollisions(&bombs, &players))
			playerLives--;
		
	}



	/*
	 * Close down.
	 */
	rocketSprite->destroy();
	enemySprite1->destroy();
	enemySprite2->destroy();
	playerSprite->destroy();
	bombSprite->destroy();

	system->destroy();

	return 0;
}
