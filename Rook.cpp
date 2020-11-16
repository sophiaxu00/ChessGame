//Jianing Fang jfang25; Fanbo Xu fxu13; Ruixuan Zhai rzhai2
#include "Rook.h"
#include <iostream>

//This checks if the movement of rook is legal based on our basic rules
bool Rook::legal_move_shape(std::pair<char, char> start, std::pair<char, char>end)const{
  //check if the movement only changes one of the two parameters
  //It might move straight up or down or only right or left
  if ((start.first-end.first==0) || (start.second-end.second==0)) {
    return true;
  }
  return false;
}
