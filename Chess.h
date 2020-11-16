//Fanbo Xu; Ruixuan Zhai; Jianing Fang                                                    
//fxu13; rzhai2; jfang25

#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include "Piece.h"
#include "Board.h"

class Chess {

public:
  // This default constructor initializes a board with the standard
  // piece positions, and sets the state to white's turn
  Chess();

  // Returns a constant reference to the board
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  const Board& get_board() const { return board; }

  // Returns true if it is white's turn
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  bool turn_white() const { return is_white_turn; }
  
  void set_white(bool white);
  
  // Attemps to make a move. If successful, the move is made and
  // the turn is switched white <-> black
  bool make_move(std::pair<char, char> start, std::pair<char, char> end);

  //copy of test_move but without error message
  bool test_move(std::pair<char, char> start, std::pair<char, char> end);
  
  // Returns true if the designated player is in check
  bool in_check(bool white) const;
  
  // Returns true if the designated player is in mate
  bool in_mate(bool white) const;
  
  // Returns true if the designated player is in stalemate
  bool in_stalemate(bool white) const;
  
  Board& read_in() {return board;}
  
  //clear the whole board
  void clear_board();
  ~Chess() {clear_board();};
private:
  // The board
  Board board;
  
  // Is it white's turn?
  bool is_white_turn;
  
  //make_move's helper function, check if the two pairs themselves make sense
  bool check_pair(std::pair<char, char> start, std::pair<char, char> end) const;
  
  //make_move's helper function check if there is anything on the start position, if yes, what is it and if it has the legal movement shape
  bool check_start(std::pair<char, char> start) const;
  
  //make_move's helper function check if there is anything between end and start
  //this has to be checked for every piece except for knight/king
  bool check_path(std::pair<char, char> start, std::pair<char, char> end, Board& board) const;
  
  //make_move's helper function check if there is anything at the end of the movement
  bool check_end(std::pair<char, char> start, std::pair<char, char> end) const;
  
  //a function that check if a player can make any legal move
  bool any_move(bool white) const;
};

// Writes the board out to a stream
std::ostream& operator<< (std::ostream& os, const Chess& chess);

// Reads the board in from a stream
std::istream& operator>> (std::istream& is, Chess& chess);


#endif // CHESS_H
