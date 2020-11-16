//Jianing Fang jfang25; Fanbo Xu fxu13; Ruixuan Zhai rzhai2
#include "Queen.h"
#include <iostream>

//check if the movement of the queen follows the basic rule of chess
bool Queen::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  //the basic movement of queen is the combination of bishop and rook
  
  if ((start.first-end.first==0) || (start.second-end.second==0)) {
    //if it moves like rook
    return true;
  }
  
  else if ((end.first-start.first==end.second-start.second) || (end.first-start.first==start.second-end.second)){
    //if it moves like bishop
    return true;
  }
  return false;
}
