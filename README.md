### *This project has been created as part of the 42 curriculum by mfornovi and frlorenz*

# Description

Cub3d is the second grafic project in 42 commond core, in this project we learn how create a simple raycast
and use it to paint the illusion of a 3D maze on a window and walk around inside it as the famous Wolfestein game.


# Instructions

## Clone

Clone the repository:

```shell
git clone https://github.com/magamaganific/Cub3d.git
```

## Compile and Run

To compile the mandatory part, `cd` into the cloned directory and:

```shell
make
```

To run the program:

```shell
./cub3d <path/to/map.cub>
```

The program takes a map file as an argument. Maps are available in the `maps` directory.

For example:

- `./cub3d maps/map.cub`

Because a graphics library is required, and the MLX42 library from codam has been chosen before compilation, running `make` automatically clones the library from github https://github.com/codam-coding-college/MLX42 and compiles it before compiling the entire project.

`An internet connection is required to download the MLX42 library.`


## Controls

Here is a summary of the various controls in the game:

- The ``WASD`` keys move the player up, down, left and right relative to the player's viewing angle
- The ``left`` and ``right`` arrow keys rotate the viewing angle of the player
- Press the ``ESC`` key or the ``X`` button on the window to exit the game

## Configuration

The game requires a valid configuration file with the extension *"map.cub"* as a parameter. This configuration file will contain the paths to the texture files to be displayed, as well as the RGB colors used to represent the ceiling and floor of the maze, in addition to the map itself.

The configuration file must adhere to the following format:

- The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player’s start position and spawning
orientation.

- The map must be closed/surrounded by walls, if not the program must return
an error.

- Except for the map content, each type of element can be separated by one or
more empty lines.

- Except for the map content which always has to be the last, each type of
element can be set in any order in the file.

- Except for the map, each type of information from an element can be separated
by one or more spaces.

- The map must be parsed as it looks in the file. Spaces are a valid part of the
map and are up to you to handle. You must be able to parse any kind of map,
as long as it respects the rules of the map.

- Except for the map, each element must begin with its type identifier (composed
by one or two characters), followed by its specific information in a strict order:
	
	- NO => North texture
	- SO => South texture
	- WE => West texture
	- EA => East texture
	- F => Floor color
	- C => Ceiling color
### Configuration example:
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 4,204,184
C 29,150,85

 111111111        111111111111111111 
1000000000111111110000000001000011001
10001000000000000000000000001111100001
1000000000000000000N000000000000000001
10001001000001000001000001000001000001
10000000000000000000000000000000000001
10001000001000001000001000001000001001
10000000000000000000000000000000000001
 100000000000000000000000000000000001
  1000000000000001001100000000000001
   10000000000000010100000000000001
    111111111111111111111111111111
```

# Resources

We didn´t use the AI for this project, only peer to peer and patience.

### websites of interest:
https://lodev.org/cgtutor/raycasting.html

https://timallanwheeler.com/blog/2023/04/01/wolfenstein-3d-raycasting-in-c/

### Special thanks to:

- psapio
- dgargant
- ldel-val
- ymunoz-m