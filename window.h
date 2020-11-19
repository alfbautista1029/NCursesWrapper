//
//  window.h
//  ncurses_abridged
//
//  Created by Alfredo Bautista on 11/17/20.
//

#ifndef window_h
#define window_h

#include <ncurses.h>
#include <stdlib.h>
#include <wchar.h>
#include <clocale>

//this array of type cchar_t is the default border used for windows
extern cchar_t* norm_border[8];


//the coordinate structure groups together the y and x cooridinates of the screen 
typedef struct
{
	int line_y, col_x;
} cord;

class window
{
	private:
		//main window pointer for use with the ncurses library
		WINDOW* _win;
		
		/*
			the starting and ending cooridinates of the window
			
			_wbeg details where the window's origin will be.
			_wend details the last point of the window as well as the window's size
		 */
	
		cord _wbeg;
		cord _wend;
		
		/* 
		   the starting and ending cooridinate positions for the cursor.
		   
		   these coordinates set limits on where the cursor is able to print characters
		   to avoid having the cursor overwrite the window's border
		 */
		cord _cbeg;
		cord _cend;
		
		// the current cooridinate position of the cursor 
		cord _cpos;
	
		// an array of type cchar_t (for wide character support) that holds the characters for the
		// window's border
		cchar_t* _border[8];
	
		//this integer will hold the window's current color pair (color text on color background)
		int _color_pair;
		
	public:
		//main window functions
		
		// creates a default window at the origin (0,0) that is the size of the current terminal window, 
		// and has a default border set using the norm_border array.
		window();
		
		//constructor that sets up a window based on the beginning and ending coordinates for the window 
		window(cord, cord);
	
		//copy constructor
		window(window&);
		
		//returns the window's WINDOW pointer 
		virtual WINDOW* get_win();
		
		//returns the window's beginning cooridinate
		virtual void get_wbeg(cord &);
		
		//returns the windows ending cooridinate
		virtual void get_wend(cord &);
		
		//returns the beginning cooridinate limit for the cursor
		virtual void get_cbeg(cord &);
		
		//sets the beginning cooridinate limit for the cursor
		virtual void set_cbeg(cord);
		
		//returns the ending cooridinate limit for the cursor
		virtual void get_cend(cord &);
		
		//sets the beginning cooridinate limit for the cursor
		virtual void set_cend(cord);	
		
		//returns the current cursor position
		virtual void get_cpos(cord &);
		
		//sets the beginning cooridinate limit for the cursor
		virtual void set_cpos(cord);
		
		//returns the current border array
		virtual cchar_t** get_border();
			
		//sets a new border configuration - follows the same layout as the ncurses defined wborder_set(...) 
		virtual void set_border(cchar_t** new_border);
		
		//draws the border around the window using the characters stored in the member _border array
		virtual void draw_border();
		
		//refreshes the window and the ncurses-defined standard screen (stdscr) window 
		virtual void win_refresh();
	
		//clears the window (erases the border and any text in the window
		virtual void win_clear();
	
		//sets the window's current color pair
		virtual void set_color_pair(int new_pair);
		
		//returns the window's current color pair
		virtual int get_color_pair();
	
		//move the window's cursor to the specified 
		virtual void cur_move(cord);
};

class sub_window : public window
{
	private:
		window* parent;
		//main subwindow pointer that is linked with a parent window 
		WINDOW* s_win;
		
		/*
			the starting and ending cooridinates of the subwindow
			
			s_wbeg details where the window's origin will be.
			s_wend details the last point of the window as well as the window's size relative to the parent window
		 */

		cord s_wbeg;
		cord s_wend;
		
		/* 
		   the starting and ending cooridinate positions for the subwindow's cursor.
		   
		   these coordinates set limits on where the cursor is able to print characters
		   to avoid having the cursor overwrite the subwindow's border
		 */
		cord s_cbeg;
		cord s_cend;
		
		// the current cooridinate position of the cursor 
		cord s_cpos;

		// an array of type cchar_t (for wide character support) that holds the characters for the
		// window's border
		cchar_t* s_border[8];

		//this integer will hold the window's current color pair (color text on color background)
		int s_color_pair;
	
		//the default constructor is privated, because it wouldn't make sense to create a subwindow
		//without having a parent window 
		sub_window();
	
	public:
	
	//constructor that takes *in a parent window object to link to
	sub_window(window* par);
	
	//constructor that takes in a parent window as well as a beginning and ending coordinate
	sub_window(window* par, cord s_wbeg, cord s_wend);
	
	//returns the sub window's WINDOW pointer
	WINDOW* get_win();
	
	//returns the sub_window's beginning cooridinate
	void get_wbeg(cord &);
	
	//returns the sub_window's ending cooridinate
	void get_wend(cord &);
	
	//returns the beginning cooridinate limit for the sub_window's cursor
	void get_cbeg(cord &);
	
	//sets the beginning cooridinate limit for the sub_window's cursor
	void set_cbeg(cord);
	
	//returns the ending cooridinate limit for the sub_window's cursor
	void get_cend(cord &);
	
	//sets the beginning cooridinate limit for sub_window's the cursor
	void set_cend(cord);	
	
	//returns the current sub_window's cursor position
	void get_cpos(cord &);
	
	//sets the beginning cooridinate limit for the sub_window's cursor
	void set_cpos(cord);
	
	//returns the current sub_window's border array
	cchar_t** get_border();
		
	//sets a new border configuration - follows the same layout as the ncurses defined wborder_set(...) 
	void set_border(cchar_t* new_border[]);
	
	//draws the border around the sub_window using the characters stored in the member _border array
	void draw_border();
	
	//refreshes the sub_window and the ncurses-defined standard screen (stdscr) window 
	void win_refresh();

	//clears the sub_window (erases the border and any text in the window
	void win_clear();

	//sets the sub_window's current color pair
	void set_color_pair(int new_pair);
	
	//returns the sub_window's current color pair
	int get_color_pair();

	//move the sub_window's cursor to the specified 
	void cur_move(cord);
};

#endif /* window_h */
