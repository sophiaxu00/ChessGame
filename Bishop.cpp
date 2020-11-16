//Jianing Fang jfang25; Fanbo Xu fxu13; Ruixuan Zhai rzhai2
#include "Bishop.h"
#include <iostream>

//check if the movement passed in is legal based on the basic rules
bool Bishop::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const{
  //check if the difference between chars and numbers are the same
  //it has to represent the two diagonalized corners of a square
  if ((end.first-start.first==end.second-start.second) || (end.first-start.first==start.second-end.second)){
    return true;
  }
  return false;
}
