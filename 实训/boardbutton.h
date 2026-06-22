#pragma once
#include"region.h"
#include<graphics.h>
#include<iostream>
extern int board_data[5][5];
class boardbutton
{
public:
	boardbutton(RECT rect, int index, int hang, int lie_1, int initialNum) {
		regio = rect;
		xuhao = index;
		han = hang;
		lie = lie_1;
		num = initialNum; // …Ë÷√≥ı º÷µ
	}
	void set_num(int n)
	{
		num = n;
	}
	int return_number()
	{
		return num;
	}
	
	void on_update(int delta)
	{
		timer += delta;
		board_data[han][lie] = num;
		
	}
	void processevent(const ExMessage& msg)
	{
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (checkhit(msg.x, msg.y))
			{
				is_down = true;
				timer = 0;
			}
		}
		if (is_down && timer < wait_time&&msg.message==WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case '1':
				num = 1;
				is_down = false;
				break;
			case '2':
				num = 2;
				is_down = false;
				break;
			case '3':
				num = 3;
				is_down = false;
				break;
			case '4':
				num = 4;
				is_down = false;
				break;
			case '5':
				num = 5;
				is_down = false;
				break;
			default:
				break;
			}
	   }
		if (timer > wait_time)
			is_down = false;
	}
	
	void fill_color()
	{
		if (is_down)
		{
			setfillcolor(RED);
			fillrectangle(regio.left, regio.top, regio.right, regio.bottom);
		}
	}
	int returnnum()
	{
		return num;
	}
private:
	RECT regio;
	int xuhao;
	int han;
	int lie;
	int num=0;
	int timer = 0;
	int wait_time = 3000;
		
private:
	bool checkhit(int x, int y)
	{
		return x >= regio.left && x <= regio.right && y >= regio.top && y <= regio.bottom;
	}
private:
	bool is_down = false;
};