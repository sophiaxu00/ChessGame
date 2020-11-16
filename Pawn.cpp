//Jianing Fang jfang25; Fanbo Xu fxu13; Ruixuan Zhai rzhai2
#include "Pawn.h"
#include <iostream>

//This checks if the pawn moves based on the basic movement rules
bool Pawn::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end)const {
  //Pawn can only go one up
  //this is the basic movement
  if (((end.second-start.second==1) && (start.first==end.first) && is_white()) || ((end.second-start.second==-1) && (start.first==end.first) && !is_white())) {
    //if white up, if black down
    return true;
  }

  //Pawn can go two rows up if just start
  else if (((start.second=='2') && (end.second-start.second==2) && is_white() && (end.first-start.first == 0)) || ((start.second=='7') && (end.second-start.second==-2) && !is_white() && (end.first-start.first == 0))) {
    //if white up, if black down
    return true;
  }
  return false;
}

//This checks if the cpature movement looks correct
bool Pawn::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end)const{
  //see if it goes one right upper or one left upper
  if(is_white() && ((end.first-start.first==1) || (end.first-start.first==-1)) && (end.second-start.second==1)) {
    //if white, upper
    return true;
  }
  else if (!is_white() && ((end.first-start.first==1) || (end.first-start.first==-1)) && (end.second-start.second==-1)) {
    //if black, down
    return true;
  }
  return false;
}
