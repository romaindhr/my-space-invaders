# Space Invaders by Romain DUHR

## Game Description

This archive allows you to run a game coded in C based on the 1978 game Space Invaders. The principle: the player controls a green spaceship that moves along the bottom of the window from left to right. They can shoot missiles to kill enemies represented by small blue aliens. These aliens also move in groups from left to right and gradually descend towards the player. If they reach the player's level, it's game over! The aliens can also drop bombs to make the player's task more difficult. If a bomb hits a missile, both are destroyed. The player has 3 lives; if they are hit 3 times by bombs, they lose. If the player kills all the aliens, then it's a win!

## Compilation linux

In order to compile correctly, SDL1 and the TTF library must be installed correctly. To do this, you can execute the following three commands:
```
sudo apt-get upgrade
sudo apt install libsdl1.2-dev
sudo apt install libsdl-ttf2.0-dev
```

To launch the game: 
```
cd src
make & ./main
```

