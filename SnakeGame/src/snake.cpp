#include "snake.h"
#include <cmath>
#include <iostream>

Snake::Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2){ 
          
    int x_increase, y_increase;
    
    switch (direction) {
        case Direction::kUp :
            y_increase =- speed;
            break;
        case Direction::kDown :
            y_increase =+ speed;
            break;
        case Direction::kLeft :
            x_increase =- speed;
            break;
        case Direction::kRight :
            x_increase =+ speed;
    }
    for (auto cnt = 1; cnt < size; cnt++) {
        SDL_Point cell{
            static_cast<int>(head_x-(size-cnt)*x_increase),
            static_cast<int>(head_y-(size-cnt)*y_increase) };
        body.push_back(cell);
    }
     
}

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)
      };  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
    Coordinate New_Coordinate = growHead(head_x, head_y);
      
    head_x = static_cast<float> (New_Coordinate.a);
    head_y = static_cast<float> (New_Coordinate.b);
    
    auto result_fmod_x = fmod(head_x + grid_width, grid_width);
    auto result_fmod_y = fmod(head_y + grid_height, grid_height);
      
    head_x = result_fmod_x;
    head_y = result_fmod_y;
  

  /*bool redirected = false;
  Coordinate next_head = growHead(head_x, head_y);
  int x = static_cast<int>(head_x);
  int y = static_cast<int>(head_y);
  int new_x = static_cast<int>(next_head.a);
  int new_y = static_cast<int>(next_head.b);

  switch (direction) {
    case Direction::kUp:
        if (next_head.b < 0 || (y != new_y && SnakeCell(new_x, new_y)) ) {
            redirected = true;
            if (x <= 0 || SnakeCell(x - 1, y) )    
                direction = Direction::kRight;
            else
                direction = Direction::kLeft;
        }
        break;

    case Direction::kDown:
        if (next_head.b >= grid_height || (y != new_y && SnakeCell(new_x, new_y)) ) {
            redirected = true;
            if (x >= grid_width - 1 || SnakeCell(x + 1, y) ) 
                direction = Direction::kLeft;
            else
                direction = Direction::kRight;
        }
        break;

    case Direction::kRight:
        if (next_head.a >= grid_width || x != new_x && SnakeCell(new_x, new_y) ) {
            redirected = true;
            if (y <= 0 || SnakeCell(x, y - 1) ) 
                direction = Direction::kDown;
            else
                direction = Direction::kUp;
        }
        break;

    case Direction::kLeft:
        if (next_head.a <= 0 || x != new_x && SnakeCell(new_x, new_y)) {
            redirected = true;
            if (y >= grid_height - 1 || SnakeCell(x, y + 1) ) // can't make a left turn coz you're at BL
                direction = Direction::kUp;
            else
                direction = Direction::kDown;
        }
        break;
  }

  if (redirected) 
      next_head = growHead( head_x , head_y );
   
  head_x = next_head.a;
  head_y = next_head.b;*/
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } 
  else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }

}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {

  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }

  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

bool Snake::isAlive() const {
    return alive; 
}

Coordinate Snake::getHead() const {
    return Coordinate(head_x, head_y); 
}

void Snake::scaleSpeed(float factor){ 
    speed *= factor; 
}

int Snake::getSize() const { 
    return size; 
}

bool Snake::sizeInBoundary(int lower, int higher) const {
    return size > lower && size < higher; 
}

Coordinate Snake::growHead( float a, float b) {
    switch (direction) {
    case Direction::kUp:
        b -= speed;
        break;

    case Direction::kDown:
        b += speed;
        break;

    case Direction::kLeft:
        a -= speed;
        break;

    case Direction::kRight:
        a += speed;
        break;
    }
    return Coordinate(a, b);
}

std::vector<int> Snake::next_cell() {
    // given current direction and head coordinates, what is the next cell?
    std::vector<int> next_point{ 0,0 };
    int x1 = static_cast<int>(head_x);
    int y1 = static_cast<int>(head_y);
    
    switch (direction) {
    case Direction::kUp:
        y1 -= 1;
        break;

    case Direction::kDown:
        y1 += 1;
        break;

    case Direction::kLeft:
        x1 -= 1;
        break;

    case Direction::kRight:
        x1 += 1;
        break;
    }
    next_point[0] = x1;
    next_point[1] = y1;
    return next_point;
}
