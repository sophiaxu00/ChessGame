//Jianing Fang jfang25; Fanbo Xu fxu13; Ruixuan Zhai rzhai2
#include <iostream>
#include <utility>
#include <map>
#include "Board.h"
#include "CreatePiece.h"
#include "Terminal.h"

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Board::Board(){}

const Piece* Board::operator()(std::pair<char, char> position) const {
  //check if there is a piece at the position
  if (occ.find(position) != occ.cend()) {
    return occ.find(position)->second;
  }
  //return null if there is not a piece
  return nullptr;
}


bool Board::add_piece(std::pair<char, char> position, char piece_designator) {
  //check if the designator is valid using create_piece function
  Piece* temp = create_piece(piece_designator);
  if (temp == nullptr) {
    return false;
  }
  //check if the specified location is not on the board
  else if ((!(position.first <= 'H')) || (!(position.first >= 'A')) || (!(position.second <= '8')) || (!(position.second >= '1'))) {
    return false;
  }
  //check if the position is occupied
  else if (occ.find(position) != occ.cend()) {
    return false;
  }
  //if pass all requirement, add it to the position
  occ[position] = temp;
  return true;
}

//after scanning the file, use this function to check if the board is valid
bool Board::has_valid_kings() const {
  int count_K = 0;//count the number of white king
  int count_k = 0;//count the number of black king
  for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.cbegin(); it != occ.cend(); ++it) {
    if (it->second->to_ascii() == 'K') {
      count_K += 1;
    }
    else if (it->second->to_ascii() == 'k') {
      count_k += 1;
    }
  }
  //if there is not a white king and a black king, return false
  if ((count_K != 1) || (count_k != 1)) {
    return false;
  }
  return true;
}

//display the board on the stdout
void Board::display() const {
  //Terminal::color_bg(Terminal::WHITE);
  Terminal::color_fg(true, Terminal::CYAN);
  std::cout << *this;
  Terminal::set_default();
}

//Check if there is anything between the path
bool Board::check_path(std::pair<char, char> start, std::pair<char, char> end) const {
  //Moved variable declarations outside (JF)
  char small;
  char large;
  //if the piece is going only left and right
  if (start.first == end.first) {
    if (start.second > end.second) {
      small = end.second;
      large = start.second;
    }
    else {
      small = start.second;
      large = end.second;
    }
    for (char count = small + 1; count < large; ++count) {
      if (occ.find(std::make_pair(start.first, count)) != occ.end()) {
	return false;
      }
    }
  }
  //if the piece is going only up and down
  if (start.second == end.second) {
    if (start.first > end.first) {
      small = end.first;
      large = start.first;
    }
    else {
      small = start.first;
      large = end.first;
    }
    for (char count = small + 1; count < large; ++count) {
      if (occ.find(std::make_pair(count, start.second)) != occ.end()) {
	return false;
      }
    }
  }

  //if the piece is going diagonally
  //Note(JF): moved variable declarations outside of if command to ensure they are in scope during the for loop.
  char small_letter;
  char large_letter;
  char start_num;
  int num_count = 0;
  
  if ((start.first - end.first == start.second - end.second) || (start.first - end.first == end.second - start.second)) {
    if (start.first > end.first) {
      large_letter = start.first;
      small_letter = end.first;
      start_num = end.second;
      if (end.second < start.second) {
	num_count = 1;
      }
      else {
	num_count = -1;
      }
    }
    else {
      small_letter = start.first;
      large_letter = end.first;
      start_num = start.second;
      if (start.second < end.second) {
	num_count = 1;
      }
      else {
	num_count = -1;
      }
    }
    for (char count = (char) (small_letter + 1); count < large_letter; ++count) {
      //std::cout << count << " " << (char) (small_num + count - small_letter) << std::endl;
      if (occ.find(std::make_pair(count, (char) (start_num + (count - small_letter) * num_count))) != occ.end()) {  //operator "!=" not defined.
	  //std::cout << count << (char) (small_num + (count - small_letter)) << std::endl;
	return false;
      }
    }
  }
  //if all the tests pass, return true
  //if knight, pawn, king, return true
  return true;
}

//erase a piece
void Board::clear(std::pair<char, char> position) {
  delete (*this)(position);
  occ.erase(position);
}

Board::~Board() {
  for (char num = '8'; num >= '1'; --num) {
    for (char letter = 'A'; letter <= 'H'; ++letter) {
      if ((*this)(std::make_pair(letter, num)) != NULL) {
	clear(std::make_pair(letter, num));
      }
    }
  }
}
/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Board& board) {
	for(char r = '8'; r >= '1'; r--) {
		for(char c = 'A'; c <= 'H'; c++) {
			const Piece* piece = board(std::pair<char, char>(c, r));
			if (piece) {
				os << piece->to_ascii();
			} else {
			  os << '-';
			}
		}
		os << std::endl;
	}
	return os;
}

