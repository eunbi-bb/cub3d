# cub3D
![cub3d](https://github.com/eunbi0308/cub3d/assets/80834766/9df0df75-1788-4c75-8a53-e438f2450d7d)

*Creating a 3D graphical representation of the inside of a maze from a first-person perspective by using the Ray-Casting principles.*

## Usage
- **Execute**
```
$ make
```
```
$ ./cub3D ./maps/map1.cub
```
- **Move** \
`W`,`A`,`S` and `D` keys
- **Rotate** \
`←` or `→` Left or right arrow keys
- **Quit** \
Pressing `ESC` or Clicking a `cross button` on the window's frame.

## *Parser*
Parsing all information from a `.cub` file to execute.\
A `.cub` file contains below informatin.
  - A map is composed of `1`(wall) and `0`(empty space).
  - Player's start position and orientation(`N`,`S`,`E` or `W`).
  - The texture path of each wall according to the direction.\
    North texture : `NO ./path_to_the_north_texture`\
    South texture : `SO ./path_to_the_south_texture`\
    West texture  : `WE ./path_to_the_west_texture`\
    East texture  : `EA ./path_to_the_east_texture`
  - Floor and Ceiling RGB color
    Floor color : `F 200,100,0`
    Ceiling color : `C 225,30,0`\
*Example of `map.cub`*
![image](https://github.com/eunbi0308/cub3d/assets/80834766/903eb2c1-4148-474a-b523-3808f2c22738)

The parser is detecting misconfiguration of any kind is encounted in the file. For example,
- The map is closed/surreounded by walls.
- The map is composed of only 6 possible characters : `0`, `1` and `N` `S` `E` or `W`.
- If each type of element can be separated by one or more empty line(s) except for the map content.

## *Render*
Representing Ray-casting with the *DDA(Digital Differential Analyzer) as known as the Line Drawing Algorithm*.\
[Resource for Ray-casting(In Korean)](https://github.com/mathreboot/raycast)

The algorithm is applied to [src/render](src/render).

To render the map, first, cast rays form the player's position through each pixel on the screen.\
To check for intersections between the cast rays and the walls in the scene,\
the DDA algorithm helps stepping through the ray and checking for intersections with walls.\
In my code, it's applied to [get_intersection](src/render/ray_casting.c).\
The intersections are checked both horizontally and vertically. \
To determine the 'real' wall, find the closest intersection from the player, \
considering both horizontal and vertical intersections. Once all rays have been cast and intersections checked, \
use the depth information to determine the height of the wall on the screen.\
Finally Render the scene by drawing vertical lines based on their height and distance from the player.

---
## *Other Resources about ray casting*
[Make Your OWn Raycaster](https://youtu.be/gYRrGTC7GtA?feature=shared)

