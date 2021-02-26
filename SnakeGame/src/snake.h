#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

#define INI_LENGTH 2

class Coordinate {
public :
	float a;
	float b;
	Coordinate(float X, float Y) : a(X), b(Y) {};	
};

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height);
  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);
  
  bool isAlive() const;
  Coordinate getHead() const;
  const std::vector<SDL_Point>& getBody() const { return body; }

  void scaleSpeed(float factor);
  int getSize() const;
  bool sizeInBoundary(int lower, int higher) const;

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{INI_LENGTH};
  bool alive{true};
  float head_x;
  float head_y;
   
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  
  Coordinate growHead(float, float);
  std::vector<int> next_cell();

  bool growing{false};
  int grid_width;
  int grid_height;

};

#endif