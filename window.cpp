//
//  window.cpp
//  ncurses_abridged
//
//  Created by Alfredo Bautista on 11/17/20.
//

#include "window.h"

//these cchar_t variables make up the normal default border on any window.
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


/**********************************window class definitions BEGIN********************************************/
window::window()
{
	_wbeg = {0, 0};
	_wend = {LINES - 1, COLS - 1};
	_cbeg = {1, 1};
	_cend = {LINES - 2, COLS - 2};
	_cpos = {1, 1};
	_win = newwin(_wend.line_y, _wend.col_x, _wbeg.line_y, _wbeg.col_x);
	set_border(norm_border);
	_color_pair = 1;
	_cpos.line_y = _cbeg.line_y;
	_cpos.col_x = _cbeg.col_x;
	wmove(_win, _cpos.line_y, _cpos.col_x);
	init_pair(_color_pair, COLOR_WHITE, COLOR_BLACK);
	wbkgd(_win, COLOR_PAIR(_color_pair));
}

window::window(cord begin, cord end)
{
	if(begin.line_y < 0)
		begin.line_y = 0;
	if(begin.col_x < 0)
		begin.col_x = 0;
	
	if(end.line_y >= LINES)
		end.line_y = LINES - 1;
	if(end.col_x >= COLS)
		end.col_x = COLS - 1;
	
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
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		wbkgd(_win, COLOR_PAIR(1));
	}	
}
window::window(window &orig)
{

	 _win = orig._win;
	_wbeg = orig._wbeg;
	_wend = orig._wend;
	_cbeg = orig._cbeg;
	_cend = orig._cend;
	_cpos = orig._cpos;
	_color_pair = orig._color_pair;
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
	_color_pair = new_pair;
	wbkgd(_win, COLOR_PAIR(_color_pair));
}

int window::get_color_pair()
{
	return _color_pair;
}

void window::cur_move(cord new_pos)
{
	_cpos.line_y = new_pos.line_y;
	_cpos.col_x = new_pos.col_x;
	wmove(_win, _cpos.line_y, _cpos.col_x);
}
/**********************************window class definitions END********************************************/












/**********************************sub_window class definitions BEGIN************************************/
sub_window::sub_window(window* par, cord begin, cord end) : parent(par)
{
	cord* par_beg = new cord;
	cord* par_end = new cord;
	parent->get_wbeg(*par_beg);
	parent->get_wend(*par_end);
	
	if(begin.line_y <= par_beg->line_y)
		s_wbeg.line_y = par_beg->line_y + 1;
	if(begin.col_x <= par_beg->col_x)
		s_wbeg.col_x = par_beg->col_x + 1;
	
	if(end.line_y >= par_end->line_y)
		s_wend.line_y = par_end->line_y - 1;
	if(end.col_x >= par_end->col_x)
		s_wend.col_x = par_end->col_x - 1;
	
	s_wbeg = begin;
	s_wend = end;
	
	s_cbeg = {(s_wbeg.line_y + 1), (s_wbeg.col_x + 1)};
	s_cend = {(s_wend.line_y - 1), (s_wend.col_x - 1)};
	
	s_win = subwin(par->get_win(), s_wend.line_y, s_wend.col_x, s_wbeg.line_y, s_wbeg.col_x);
	set_border(norm_border);
	s_color_pair = 0;
	s_cpos.line_y = s_cbeg.line_y;
	s_cpos.col_x = s_cbeg.col_x;
	
	wmove(s_win, s_cpos.line_y, s_cpos.col_x);
	
	if(has_colors())
	{
		init_pair(1, COLOR_BLACK, COLOR_WHITE);
		wbkgd(s_win, COLOR_PAIR(1));
	}

	delete par_beg;
	delete par_end;
}

WINDOW* sub_window::get_win()
{
	return s_win;
}

void sub_window::get_wbeg(cord &co)
{
	co.line_y = s_wbeg.line_y;
	co.col_x = s_wbeg.col_x;
}

void sub_window::get_wend(cord &co)
{
	co.line_y = s_wend.line_y;
	co.col_x = s_wend.col_x;
}

void sub_window::get_cbeg(cord &co)
{
	co.line_y = s_cbeg.line_y;
	co.col_x = s_cbeg.col_x;
}

void sub_window::set_cbeg(cord co)
{
	if(co.line_y <= s_wbeg.line_y)
		co.line_y = s_wbeg.line_y + 1;
	else if(co.line_y >= s_wend.line_y)
		co.line_y = s_wend.line_y - 1;
		
	if(co.col_x <= s_wbeg.col_x)
		co.col_x = s_wbeg.col_x + 1;
	else if(co.col_x >= s_wend.col_x)
		co.col_x = s_wend.col_x - 1;
	
	
	s_cbeg.line_y = co.line_y;
	s_cbeg.col_x = co.col_x;
}

void sub_window::get_cend(cord &co)
{
	co.line_y = s_cend.line_y;
	co.col_x = s_cend.col_x;
}

void sub_window::set_cend(cord co)
{
	if(co.line_y <= s_wbeg.line_y)
		co.line_y = s_wbeg.line_y + 1;
	else if(co.line_y >= s_wend.line_y)
		co.line_y = s_wend.line_y - 1;
		
	if(co.col_x <= s_wbeg.col_x)
		co.col_x = s_wbeg.col_x + 1;
	else if(co.col_x >= s_wend.col_x)
		co.col_x = s_wend.col_x - 1;
	
	wmove(s_win, co.line_y, co.col_x);
}

void sub_window::get_cpos(cord &co)
{
	co.line_y = s_cpos.line_y;
	co.col_x = s_cpos.col_x;
}

void sub_window::set_cpos(cord co)
{
	if(co.line_y <= s_wbeg.line_y)
		co.line_y = s_wbeg.line_y + 1;
	else if(co.line_y >= s_wend.line_y)
		co.line_y = s_wend.line_y - 1;
		
	if(co.col_x <= s_wbeg.col_x)
		co.col_x = s_wbeg.col_x + 1;
	else if(co.col_x >= s_wend.col_x)
		co.col_x = s_wend.col_x - 1;
	
	wmove(s_win, co.line_y, co.col_x);
}

cchar_t** sub_window::get_border()
{
	return s_border;
}

void sub_window::set_border(cchar_t* new_border[])
{
	for(int count = 0; count < 8; count++)
	{
		s_border[count] = new_border[count];
	}
}

void sub_window::draw_border()
{
	wborder_set(s_win, s_border[0], s_border[1], s_border[2], s_border[3], s_border[4], s_border[5], s_border[6], s_border[7]);
}

void sub_window::win_refresh()
{
	refresh();
	wrefresh(parent->get_win());
	wrefresh(s_win);
}

void sub_window::win_clear()
{
	wclear(s_win);
	win_refresh();
}

void sub_window::set_color_pair(int new_pair)
{
	wbkgd(s_win, COLOR_PAIR(new_pair));
}

int sub_window::get_color_pair()
{
	return s_color_pair;
}

void sub_window::cur_move(cord new_pos)
{
	s_cpos.line_y = new_pos.line_y;
	s_cpos.col_x = new_pos.col_x;
	wmove(s_win, s_cpos.line_y, s_cpos.col_x);
}
/**********************************sub_window class definitions END**************************************/
