//Jianing Fang jfang25; Fanbo Xu fxu13; Ruixuan Zhai rzhai2
#include "Knight.h"
#include <iostream>

//check if the movement is legal based on the basic rule
bool Knight::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  //it can go the diagonal of a one by two or two by one rectangle
  if ((((start.first-end.first==1) || (start.first-end.first==-1)) && ((start.second-end.second==2) ||(start.second-end.second==-2))) || (((start.first-end.first==2) || (start.first-end.first==-2)) && ((start.second-end.second==1) || (start.second-end.second==-1)))) {
    return true;
  }
  return false;
}
