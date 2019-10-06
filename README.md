# Filler

The algorithmic project at School 42.

The objective is to write a player program, that will compete in filling a board with random figures against other players

![visualization](visual.gif)

### The Virtual Machine

The program 'filler_vm' is provided by the subject

It will load a map file and players files

It will execute players, generate figures for them and place these figures onto map by the coordinates it gets from players

### Players

Players are named as 'username.filler'

Players read board and figures from 'filler_vm' and output coordinates for vm

Some example players are also provided by the subject, by subject written player has to beat them all

### Figures

Figures are random, they have rectangle shape and piece inside of it

Shape must fit into board, and piece should overlap with exatly one dot from previous pieces, thus all placed figures are connected with each other

Example of figure

```
. . . .
. . * *
. * * .

```

### Installing

The project was written and tested on macOS Sierra with SDL2 library for visualization, which is included into this repository

```
git clone --recursive https://github.com/hauh/filler.git filler && cd filler && make
```

### Usage

```
./resources/filler_vm -f 'path_to_map' -p1 'path_to_player_1' -p2 'path_to_player_2' [-s seed]
					  you can use pipe to redirect output to ./filler_visual
```
Filler_vm, maps and players are located in 'resources' directory, my player is 'smorty.filler' in the root directory

### Algorithm

* On each move generate a 'heat map', where 'temperature' of each spot is distance to opponent
* Check each possible spot for given figure and calculate total temperature of the spot
* Spot with lowest temperature is closest to opponent, this way the algorithm will try to block opponent
* When opponent is blocked, fill the board from edges to center to maximize score

### Grade

125/125
