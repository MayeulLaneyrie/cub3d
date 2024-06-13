# CUB3D

## by Mayeul Laneyrie & Said Hamizi @42Paris

This is a tiny raycasting demo, based on the 42 school minilibx library (which
is a not-so-good piece of software which usage is mandatory for students at 42,
which is quite sad, but whatever).

## Usage

`make` to compile the minimal version, then `./cub3d path_to_file` to run.
However, I recommand you compile directly with `make bonus` to enjoy all the
functionalities.

Here is a simple valid map example:

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

F and C being the colors of the floor and ceiling.

In the MAPS directory, you will find example of maps both valid and invalid
(since there is a parsing dimension to this project, correct error management
is required).

## Controls

- `[w/a/s/d]` to move (sorry for AZERTY keyboard users, I quite didn't implemented
keyboard configuration...)
- `[tab]` to sprint
- `[m]` toggle minimap
- `[x]` close window and leave
