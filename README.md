# Generic Top Down Shooter (C++,SDL)
## Summary
This game was made in c++ using SDL for an assignment. The goal of the assignment was to teach us about basic c++ game making, using extended programming libraries such as SDL
and implementing design patterns. My game is a top down shooter where you have to kill as many enemies as possible to achieve a higher score. If an enemy touches you, you die and have to restart.


## Design patterns
Design patterns I used to achieve this was Subclass Sandbox and Type object pattern to make Gameobjects that have basic functions like handleEvent, update and render.
I then used this class to create all of my objects in my game like the player, enemies and bullets. Another design pattern I used was the gameloop pattern.
In my main function I keep track of wether the player is alive or not and if so enemies spawn and if not all enemies get deleted and the player can restart the level.

## C++ Advanced Features
Two C++ Advanced Features I used in the game was first runtime polymorphism. As all my objects in the game inherit from the base class GameObject I override the virtual functions Update,HandleEvent and Render in all my classes that inherit from GameObject. These are: Player, Enemy and Shot(the bullet).
The other Feature I use is collections. I use many different collections in my game like Strings and Vectors. Vectors I use the most and it is for keeping all the existing GameObjects in a vector where I can Update, Render, HandleEvent and delete each individual GameObject.
![image](https://github.com/forsbergsskola-se/212-cpp-game-Gandhopp/assets/112471046/426c7aa5-d366-419d-a2c6-afd56c6a2c99)

![image](https://github.com/forsbergsskola-se/212-cpp-game-Gandhopp/assets/112471046/69ef2493-44d1-4ca8-81ed-761eb66934c9)

https://github.com/forsbergsskola-se/212-cpp-game-Gandhopp/assets/112471046/3ab286a5-7e29-4fc2-a3b0-ce126a054c2d

[Build](https://github.com/forsbergsskola-se/212-cpp-game-Gandhopp/files/12227124/Release.zip)
