This game was made in c++ using SDL for an assignment. The goal of the assignment was to teach us about basic c++ game making, using extended programming libraries such as SDL
and implementing design patterns. My game is a top down shooter where you have to kill as many enemies as possible to achieve a higher score. If an enemy touches you, you die and have to restart.
Some design patterns I used to achieve this was Subclass Sandbox and Type object pattern to make Gameobjects that have basic functions like handleEvent, update and render.
I then used this class to create all of my objects in my game like the player, enemies and bullets. Another pattern I used was the gameloop pattern.
In my main function I keep track of wether the player is alive or not and if so enemies spawn and if not all enemies get deleted and the player can restart the level.

![image](https://github.com/forsbergsskola-se/212-cpp-game-Gandhopp/assets/112471046/15ee38a9-0899-464e-9b17-2714c18443ea)

![image](https://github.com/forsbergsskola-se/212-cpp-game-Gandhopp/assets/112471046/69ef2493-44d1-4ca8-81ed-761eb66934c9)

https://github.com/forsbergsskola-se/212-cpp-game-Gandhopp/assets/112471046/3ab286a5-7e29-4fc2-a3b0-ce126a054c2d
