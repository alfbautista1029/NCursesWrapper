//
//  window.cpp
//  ncurses_abridged
//
//  Created by Alfredo Bautista on 11/17/20.
//

#include "window.h"

//*these cchar_t variables make up the normal default border on any window.
cchar_t top_left = {A_NORMAL, L"\u250F"};
cchar_t top_hori = {A_NORMAL, L"\u2501"};
cchar_t top_right = {A_NORMAL, L"\u2513"};
cchar_t right_vert = {A_NORMAL, L"\u2503"};
cchar_t bot_right = {A_NORMAL, L"\u251B"};
cchar_t bot_hori = {A_NORMAL, L"\u2501"};
cchar_t bot_left = {A_NORMAL, L"\u2517"};
cchar_t left_vert = {A_NORMAL, L"\u2503"};

//an array of pointers to the previously declared cchar_t variables that are used in actually printing them onscreen
cchar_t* norm_border[8] = 
{
	&left_vert, &right_vert, &top_hori, &bot_hori, &top_left, &top_right, &bot_left, &bot_right
};

window::window()
{
	_wbeg = {0, 0};
	_wend = {LINES, COLS};
	_cbeg = {1, 1};
	_cend = {LINES - 2, LINES - 2};
	_cpos = {1, 1};
	_win = newwin(_wend.line_y, _wend.col_x, _wbeg.line_y, _wbeg.col_x);
	set_border(norm_border);
	_color_pair = 0;
	_cpos.line_y = _cbeg.line_y;
	_cpos.col_x = _cbeg.col_x;
	wmove(_win, _cpos.line_y, _cpos.col_x);
	
	if(has_colors())
	{
		init_pair(1, COLOR_BLACK, COLOR_WHITE);
		wbkgd(_win, COLOR_PAIR(1));
	}		
}

window::window(cord begin, cord end)
{
	_wbeg = begin;
	_wend = end;
	_cbeg = {(begin.line_y + 1), (begin.col_x + 1)};
	_cend = {(end.line_y - 1), (end.col_x - 1)};
	_win = newwin(_wend.line_y, _wend.col_x, _wbeg.line_y, _wbeg.col_x);
	set_border(norm_border);
	_color_pair = 0;
	_cpos.line_y = _cbeg.line_y;
	_cpos.col_x = _cbeg.col_x;
	wmove(_win, _cpos.line_y, _cpos.col_x);
	
	if(has_colors())
	{
		init_pair(1, COLOR_BLACK, COLOR_WHITE);
		wbkgd(_win, COLOR_PAIR(1));
	}	
}

WINDOW* window::get_win()
{
	return _win;
}

void window::get_wbeg(cord &co)
{
	co.line_y = _wbeg.line_y;
	co.col_x = _wbeg.col_x;
}

void window::get_wend(cord &co)
{
	co.line_y = _wend.line_y;
	co.col_x = _wend.col_x;
}

void window::get_cbeg(cord &co)
{
	co.line_y = _cbeg.line_y;
	co.col_x = _cbeg.col_x;
}

void window::set_cbeg(cord co)
{
	if(co.line_y <= _wbeg.line_y)
		co.line_y = _wbeg.line_y + 1;
	else if(co.line_y >= _wend.line_y)
		co.line_y = _wend.line_y - 1;
		
	if(co.col_x <= _wbeg.col_x)
		co.col_x = _wbeg.col_x + 1;
	else if(co.col_x >= _wend.col_x)
		co.col_x = _wend.col_x - 1;
	
	
	_cbeg.line_y = co.line_y;
	_cbeg.col_x = co.col_x;
}

void window::get_cend(cord &co)
{
	co.line_y = _cend.line_y;
	co.col_x = _cend.col_x;
}

void window::set_cend(cord co)
{
	if(co.line_y <= _wbeg.line_y)
		co.line_y = _wbeg.line_y + 1;
	else if(co.line_y >= _wend.line_y)
		co.line_y = _wend.line_y - 1;
		
	if(co.col_x <= _wbeg.col_x)
		co.col_x = _wbeg.col_x + 1;
	else if(co.col_x >= _wend.col_x)
		co.col_x = _wend.col_x - 1;
	
	wmove(_win, co.line_y, co.col_x);
}

void window::get_cpos(cord &co)
{
	co.line_y = _cpos.line_y;
	co.col_x = _cpos.col_x;
}

void window::set_cpos(cord co)
{
	if(co.line_y <= _wbeg.line_y)
		co.line_y = _wbeg.line_y + 1;
	else if(co.line_y >= _wend.line_y)
		co.line_y = _wend.line_y - 1;
		
	if(co.col_x <= _wbeg.col_x)
		co.col_x = _wbeg.col_x + 1;
	else if(co.col_x >= _wend.col_x)
		co.col_x = _wend.col_x - 1;
	
	wmove(_win, co.line_y, co.col_x);
}

cchar_t** window::get_border()
{
	return _border;
}

void window::set_border(cchar_t* new_border[])
{
	for(int count = 0; count < 8; count++)
	{
		_border[count] = new_border[count];
	}
}

void window::draw_border()
{
	wborder_set(_win, _border[0], _border[1], _border[2], _border[3], _border[4], _border[5], _border[6], _border[7]);
}

void window::win_refresh()
{
	refresh();
	wrefresh(_win);
}

void window::win_clear()
{
	wclear(_win);
	win_refresh();
}

void window::set_color_pair(int new_pair)
{
	wbkgd(_win, COLOR_PAIR(new_pair));
}

int window::get_color_pair()
{
	return _color_pair;
}
