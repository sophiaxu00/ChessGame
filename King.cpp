//Jianing Fang jfang25; Fanbo Xu fxu13; Ruixuan Zhai rzhai2
#include "King.h"
#include <iostream>

//check if the moving is legal based on the basic rule of movement
//King can go only one unit but can go any direction
bool King::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  //iff one of the two pair values moves one
  if ((((start.first-end.first==1) || (start.first-end.first==-1)) && (start.second-end.second==0)) || ((start.first-end.first==0) && ((start.second-end.second==1) || (start.second-end.second==-1)))){
    return true;
  }
  else if (((start.first - end.first == start.second - end.second) || (start.first - end.first == end.second - start.second))&& ((start.first - end.first == 1) || (start.first - end.first == -1)) ) {
    return true; 
  }
  return false;
}
