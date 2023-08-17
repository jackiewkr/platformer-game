# Platformer Game

This codebase is meant to be a modular and easily-customizeable 2D tile-based
platformer engine with capabilities to be expected of other comparable engines.

Each level is split into multiple rooms that contain tilemaps and objects, such
as monsters to avoid or things to interact with or tiles that move/disappear.


## Expected Features

- Support for an arbitrary amount of tilemaps per room
- Raycasting physics engine
- Support for fragment shaders

## This Branch

This branch 'rework' is the main branch for all the branches used for reworking
the existing codebase to use GLFW for its backend as well as removing any
unnecessary libraries as work progresses.

### To-Do List

- Rework draw libraries to use GLFW instead of Allegro
- Rework events system to include more features (arbitrary timers, etc.)
- Rework levels to allow for rooms
- Include JSON parser for loading custom assets in (levels, tilemaps, objects, 
  etc.)
- Include unit testing for each library

## Instructions For Use

To compile the program, run:
'make build'
To compile with debug enabled, run:
'make debug'

To initiate testing for the program, run:
'make test'


