# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.


**Rubric Criteria**
–––––––––––––––––––

- The project demonstrates proficiency with C++ functions, control flows, and fundamental syntax.
- The project incorporates Object Oriented Programming techniques and design principles.
- Classes appropriately leverage access modifiers on members:
      - Public and protected members in the Snake base class (snake.h)
      - Public and private members in the derived AutoSnake class (auto_snake.h)
- Constructor initialization lists are utilized to initialize class data members:
      - In Game constructor (game.cpp)
      - In both Snake and AutoSnake constructors (snake.h, auto_snake.h)
- Classes hide implementation details in the .cpp file and expose clean interfaces in the header.
- Classes exhibit encapsulation by bundling relevant data and behaviors.
- An inheritance hierarchy is implemented with derived subclasses inheriting base class functionality:
      - AutoSnake inherits from Snake
      - Composition relationship with Game class
- Derived classes override key virtual functions from the base class:
      - Virtual functions defined in Snake (snake.h)
      - Overridden in AutoSnake (auto_snake.h)
- References are used appropriately in function declarations to avoid unnecessary copying.
- Move semantics are leveraged where applicable to avoid copies (auto_snake.h)
- Multithreading is incorporated in the project structure (game.cpp).
- Mutexes or locks safely handle concurrent access of shared data:
      - std::unique_lock used in snake.cpp and auto_snake.cpp


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
