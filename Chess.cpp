//Fanbo Xu; Ruixuan Zhai; Jianing Fang                                                    
//fxu13; rzhai2; jfang25

#include "Chess.h"
#include "CreatePiece.h"
#include <iostream>
using std::cout;
/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Chess::Chess() : is_white_turn(true) {
  // Add the pawns
  for (int i = 0; i < 8; i++) {
    board.add_piece(std::pair<char, char>('A' + i, '1' + 1), 'P');
    board.add_piece(std::pair<char, char>('A' + i, '1' + 6), 'p');
  }
  // Add the rooks
  board.add_piece(std::pair<char, char>( 'A'+0 , '1'+0 ) , 'R' );
  board.add_piece(std::pair<char, char>( 'A'+7 , '1'+0 ) , 'R' );
  board.add_piece(std::pair<char, char>( 'A'+0 , '1'+7 ) , 'r' );
  board.add_piece(std::pair<char, char>( 'A'+7 , '1'+7 ) , 'r' );

  // Add the knights
  board.add_piece(std::pair<char, char>( 'A'+1 , '1'+0 ) , 'N' );
  board.add_piece(std::pair<char, char>( 'A'+6 , '1'+0 ) , 'N' );
  board.add_piece(std::pair<char, char>( 'A'+1 , '1'+7 ) , 'n' );
  board.add_piece(std::pair<char, char>( 'A'+6 , '1'+7 ) , 'n' );

  // Add the bishops
  board.add_piece(std::pair<char, char>( 'A'+2 , '1'+0 ) , 'B' );
  board.add_piece(std::pair<char, char>( 'A'+5 , '1'+0 ) , 'B' );
  board.add_piece(std::pair<char, char>( 'A'+2 , '1'+7 ) , 'b' );
  board.add_piece(std::pair<char, char>( 'A'+5 , '1'+7 ) , 'b' );

  /*
  //Add the Mystery Piece
  board.add_piece(std::pair<char, char>( 'A'+0, '1'+2), 'M');
  board.add_piece(std::pair<char, char>( 'A'+0, '1'+5), 'm');
  */
  
  // Add the kings and queens
  board.add_piece(std::pair<char, char>( 'A'+3 , '1'+0 ) , 'Q' );
  board.add_piece(std::pair<char, char>( 'A'+4 , '1'+0 ) , 'K' );
  board.add_piece(std::pair<char, char>( 'A'+3 , '1'+7 ) , 'q' );
  board.add_piece(std::pair<char, char>( 'A'+4 , '1'+7 ) , 'k' );
}

bool Chess::make_move(std::pair<char, char> start, std::pair<char, char> end) {
  //check if the two pairs make sense
  if (!check_pair(start, end)) {
    std::cerr << "Invalid input position" << std::endl;
    return false;
  }
  //check if there is a piece at the start point and the movement is in legal shape
  if (!check_start(start)) {
    std::cerr << "You are moving the wrong piece, or your are not moving anything" << std::endl;
    return false;
  }
  //check if the movement shape is legal and if the capture is legal
  if (!check_end(start, end)) {
    std::cerr << "You are not moving the piece based on the legal moving shape or you are trying to eat your own piece" << std::endl;
    return false;
  }
  //check if there are any pieces in between the start and end for all pieces except for king ,pawn and knight
  if (!check_path(start, end, board)) {
    std::cerr << "You can't make the move because there are pieces in between" << std::endl;
    return false;
  }
  bool capture = false;
  char ch = 0;
  char ch_origin = 0;
  //if there is a piece, delete the piece and move the current piece to there, then delete the current piece from the old position
  if (get_board()(end) != nullptr){
    ch = get_board()(end)->to_ascii();
    board.clear(end);
    capture = true;
  }
  
  //if not a capture, just delete the old piece and create a new same piece at the new position
 
  ch_origin = get_board()(start)->to_ascii();
  board.clear(start);
  board.add_piece(end, ch_origin);
  
  if (get_board()(end)->to_ascii() == 'P' && end.second == '8') {
    board.clear(end);
    board.add_piece(end, 'Q');
  }
  
  if (get_board()(end)->to_ascii() == 'p' && end.second == '1') {
    board.clear(end);
    board.add_piece(end, 'q');
  }
  
  //check if it is in check
  if (!in_check(is_white_turn)) {
    is_white_turn = !is_white_turn;
    return true;
  }
  
  //if in check put everything back and return false
  board.clear(end);
  if (capture){
    board.add_piece(end,ch);
  }
  board.add_piece(start, ch_origin);
  return false;
}

bool Chess::test_move(std::pair<char, char> start, std::pair<char, char> end) {      
  if (!check_pair(start, end)) {
    return false;
  }
  if (!check_start(start)) {
    return false;
  }
  if (!check_end(start, end)) {
    return false;
  }
  if (!check_path(start, end, board)) {
    return false;
  }
  bool capture = false;
  char ch = 0;
  char ch_origin = 0;
  if (get_board()(end) != nullptr){
    ch = get_board()(end)->to_ascii();
    board.clear(end);
    capture = true;
  }
  ch_origin = get_board()(start)->to_ascii();
  board.clear(start);
  board.add_piece(end, ch_origin);
  
if (get_board()(end)->to_ascii() == 'P' && end.second == '8') {
    board.clear(end);
    board.add_piece(end, 'Q');
  }

  if (get_board()(end)->to_ascii() == 'p' && end.second == '1') {
    board.clear(end);
    board.add_piece(end, 'q');
  }
  //check if it is in check                                                                                                                                                                                 
  if (!in_check(is_white_turn)) {
    is_white_turn = !is_white_turn;
    return true;
  }
  board.clear(end);
  if (capture){
    board.add_piece(end,ch);
  }
  board.add_piece(start, ch_origin);
  return false;
}

bool Chess::check_pair(std::pair<char, char> start, std::pair<char, char> end) const{
  //if the position is out of range (H8 A1), it is false
  if ((start.first > 'H') || (start.first < 'A') || (end.first > 'H') || (end.first < 'A') || (start.second > '8') || (start.second < '1') || (end.second > '8') || (end.second < '1')) {
    return false;
  }
  //if the start and end position is the same, it is false
  if ((start.first - end.first == 0) && (start.second - end.second == 0)) {
    return false;
  }
  return true;
}

bool Chess::check_start(std::pair<char, char> start) const{
  const Piece* piece = board(start);
  //if there is no piece at the position, return false
  if (piece == nullptr) {
    return false;
  }
  if (is_white_turn != piece->is_white()) {
    return false;
  }
  return true;
}

bool Chess::check_path(std::pair<char, char> start, std::pair<char, char> end, Board& board) const{
  return board.check_path(start, end);
}

bool Chess::check_end(std::pair<char, char> start,std::pair<char, char> end)const{
  const Piece* piece = board(start);
  //if there is a piece at the end point
  if (board(end)!=nullptr) {
    if (board(start)->is_white() != board(end)->is_white()) {
    //see if it does the right capture movement
    return piece->legal_capture_shape(start, end);
    } else {
      return false;
    }
  }
  //if there is not a piece at the end point
  //see if it does the right movement shape
  return piece->legal_move_shape(start, end);
}

bool Chess::in_check(bool white) const {
  //obtain the position of the king
  char k_letter;
  char k_num;
  char king_letter = 0;
  if (white) {
    king_letter = 'K';
  }
  else {
    king_letter = 'k';
  }
  for (char num = '8'; num >= '1'; num--) {
    for (char letter = 'A'; letter <= 'H'; letter++) {
      std::pair<char, char> position = std::make_pair(letter, num);
      if(get_board()(position) != nullptr) {
      if(get_board()(position)->to_ascii() == king_letter) {
	k_letter = letter;
	k_num = num;
	break;
      }
      }
    }
  }
  //loop over all pieces
  for (char num  = '8'; num >= '1'; num--) {
    for (char letter = 'A'; letter <= 'H'; letter++) {
      std::pair<char, char> position = std::make_pair(letter,num);
      std::pair<char, char> king = std::make_pair(k_letter, k_num);
      //evaluate all opponent pieces
      if(board(position) != nullptr && white != get_board()(position)->is_white()) {
	//check if the opponent piece can capture the king.
	if(get_board()(position)->legal_capture_shape(position, king)) {
	  if(board.check_path(position, king)) {
	    return true;
	  }
	}
      }
    }
  }
	return false;
}

bool Chess::any_move(bool white) const {
  for (char num = '8'; num >= '1'; num--) {
    for (char letter = 'A'; letter <= 'H'; letter++) {
      std::pair<char, char> start = std::make_pair(letter, num);
      
      if(get_board()(start) != nullptr && white == get_board()(start)->is_white()) {
 
      for (char desn = '8'; desn >='1'; desn--) {
	for (char desl = 'A'; desl <= 'H'; desl++) {
	  std::pair<char, char> destination = std::make_pair(desl, desn);
	   
	  Chess * temp = new Chess();
	  temp->clear_board();
              for (char cn = '8'; cn >= '1'; cn--) {
                for (char cl = 'A'; cl <= 'H'; cl++) {
		   
		  std::pair<char, char>copy_p = std::make_pair(cl, cn);
                  if (get_board()(copy_p) != nullptr) {
                    temp->board.add_piece(copy_p, get_board()(copy_p)->to_ascii());
                  }
		}
	      }
	      // std::cout << temp->board << std::endl;
	      
	      temp->set_white(white);     
	      if (temp->test_move(start, destination)) {
		temp->clear_board();
		delete temp;
		return true;
	      }
	      temp->clear_board();
	      delete temp;
	      
	}
      }
      }
    }
  }		
  
  return false;
}

bool Chess::in_mate(bool white) const {
  if (in_check(white) && (!any_move(white))){
    return true;
  }
  //std::cout << "hello from inmate" << std::endl;
  return false;
}

bool Chess::in_stalemate(bool white) const {
  if(!in_check(white)) {
    if(any_move(white)) {
      return false;
    }
    return true;
  }
  return false;
}

void Chess::clear_board() {
  /*
  for (char num = '8'; num >= '1'; num--) {
    for (char letter = 'A'; letter <= 'H'; letter++) {
      if (board(std::make_pair(letter, num)) != NULL) {
	std::cout << "yes" << std::endl;
	board.clear(std::make_pair(letter, num));
      }
    } 
  }
  */
  board.~Board();
}

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator<< (std::ostream& os, const Chess& chess) {
	// Write the board out and then either the character 'w' or the character 'b',
	// depending on whose turn it is
	return os << chess.get_board() << (chess.turn_white() ? 'w' : 'b');
}

std::istream& operator>> (std::istream& is, Chess& chess) {
  chess.Chess::clear_board();
  for (char num = '8'; num > '0'; num--){
    for (char letter = 'A'; letter < 'I'; letter++) {
      char piece = is.get();
      while (piece == '\n') {
	piece = is.get();
      }
      if(piece != '-') {
      chess.read_in().add_piece(std::make_pair(letter, num), piece);
      }
    }
  }
  char white = is.get();
  while(white == '\n') {
  white = is.get();
  }
  chess.set_white(white == 'w');
  return is;
}

void Chess::set_white(bool white) {is_white_turn = white;}
