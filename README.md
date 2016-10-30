# dice-invaders

**Assignment:**
Create the game “Dice Invaders” using the supplied library.

**Description:**
Dice Invaders consists of four different objects: the player ship, the aliens, the aliens’ bombs and the player’s rockets. The goal of the game is to shoot as many aliens as possible without being hit by them or their bombs.

**The player ship**
The player ship is positioned at the bottom of the screen. It can only move horizontally. It can fire rockets at the aliens. The ship can take three hits from aliens or their bombs before it is destroyed and the game is over.

**The rockets**
The rockets travel straight up. If they hit an alien, the alien and the rocket are destroyed, and the player’s score is increased. Rockets cannot destroy bombs. When the rocket reaches the top of the screen, it disappears.
 
**The aliens**
The aliens start out at the top left corner of the screen, organized in rows and columns. They move slowly to the right, until the rightmost alien reaches the border of the screen. Then, they all take one step down, and start travel to the left instead. If the alien collides with the player, the alien is destroyed and the player’s health is decreased. The aliens drops bombs randomly.

**The bombs**
The bombs travel straight down. If they hit the player, the player’s health is decreased and the bomb is destroyed. When a bomb reaches the bottom of the screen, it disapears. The bombs doesn’t hurt other aliens.

**The end of the game**
If the player is hit three times by aliens or their bombs, or an alien reaches the bottom of the screen, the player loses and the game is over. If the player kills all aliens, a new alien army should be created at the top of the screen.

**The library**
Initialize the library by using the DiceInvadersLib class in example.cpp. It loads DiceInvaders.dll and provides a pointer to IDiceInvaders.
IDiceInvaders has a getElapsedTime() function, which returns the total time spent in the game, and a getKeyStatus() function, which reads input from the keyboard.
It also has methods for initializing the game window, and for creating sprites. Sprites can be drawn using the draw() function. When IDiceInvaders’s update() method is called, the screen is cleared and all drawn sprites are displayed. There is also support for drawing text messages.

**Guidelines:**

- When designing your program, find a balance between simplicity and flexibility, as you would when working in real-life. Think about what you mean with good design and express that in your solution.

- Make use of STL where appropriate.

- Think about your policy on comments. What you do you need to comment, and to what extent.

- Please use a data oriented approach (Data-oriented design) for this assignment and think about how data is accessed and arranged in memory.
