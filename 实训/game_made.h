#pragma once
#include"scenemanager.h"
#include"region.h"
#include<graphics.h>
#include <tchar.h>
#include"scenemanager.h"
#include"region.h"
extern std::vector<std::vector<int>> vec;
extern int board_data[5][5];
extern int temp_board[5][5];
extern int score;
extern scenemanager scene_manager;
class game_made :public scene
{
public:
	game_made() = default;
	~game_made() {}
	void on_enter() {
		setbkcolor(RGB(173, 216, 230));
		hasPuzzle = vec.size() == 5;
		for (int i = 0; hasPuzzle && i < 5; ++i)
		{
			hasPuzzle = vec[i].size() == 5;
		}
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
				board_data[i][j] = 0;
		}
		settextcolor(BLACK);
		if (!hasPuzzle)
		{
			return;
		}
		createtemp_vec();
		list[0].setregion(vec[0][0],vec[0][1],vec[0][2],vec[0][3],vec[0][4]);
		list[1].setregion(vec[1][0], vec[1][1], vec[1][2], vec[1][3], vec[1][4]);
		list[2].setregion(vec[2][0], vec[2][1], vec[2][2], vec[2][3], vec[2][4]);
		list[3].setregion(vec[3][0], vec[3][1], vec[3][2], vec[3][3], vec[3][4]);
		list[4].setregion(vec[4][0], vec[4][1], vec[4][2], vec[4][3], vec[4][4]);
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < temp_vec.size(); j++)
			{
				list[i].enter(temp_vec[j][0], temp_vec[j][1], temp_vec[j][2]);
			}
		}
		for (auto itr : temp_vec)
		{
			
		}
		
		
	}
	void on_update(int delta)
	{
		if (!hasPuzzle)
		{
			return;
		}
		
		for (int i = 0; i < 5; i++)
		{
			list[i].on_update(delta);
		}
		if (is_board_true() && is_all_region_full())
		{
			score = score + 10;
			scene_manager.switchto(scenemanager::scenetype::walk);
		}
	}
	void on_draw() {
		if (!hasPuzzle)
		{
			settextstyle(30, 0, _T("Arial"));
			setbkmode(TRANSPARENT);
			outtextxy(360, 280, _T("请先制作一个有效自定义题"));
			return;
		}
	
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		for (int i = 0; i < 6; i++)
		{
			line(340, 20 + 120 * i, 940, 20 + 120 * i);
			line(340 + 120 * i, 20, 340 + 120 * i, 620);
		}
		for (auto& it : list)
		{
			it.on_draw();
		}
		settextstyle(60, 0, _T("Arial"));
		setbkmode(TRANSPARENT);
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (!(board_data[i][j] == 0))
				{
					TCHAR str[32];
					_stprintf_s(str, _T("%d"), board_data[i][j]);
					outtextxy(340 + 120 * j + (120 - textwidth(str)) / 2, 20 + 120 * i + (120 - textheight(str)) / 2, str);
				}
			}
		}
		outtextxy(10, 20, _T("按E返回"));
	}
	bool is_board_true() {
		
		for (int i = 0; i < 5; ++i) {
			bool exist[5] = { false };
			for (int j = 0; j < 5; ++j) {
				int num = board_data[i][j];
				if (num < 1 || num > 5) {
					return false;
				}
				if (exist[num - 1]) {
					return false;
				}
				exist[num - 1] = true;
			}
		}

		for (int j = 0; j < 5; ++j) {
			bool exist[5] = { false };
			for (int i = 0; i < 5; ++i) {
				int num = board_data[i][j];
				if (num < 1 || num > 5) {
					return false;
				}
				if (exist[num - 1]) {
					return false;
				}
				exist[num - 1] = true;
			}
		}
		return true;
	}
	bool is_all_region_full()
	{
		for (int i = 0; i < 5; ++i)
		{
			if (list[i].returnfull() != true)
				return false;
		}
		return true;
	}
	bool all_full()
	{
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (board_data[i][j] == 0)
					return false;
			}
		}
		return true;
	}

	void on_input(const ExMessage msg) {
		if (hasPuzzle)
		{
			for (int i = 0; i < 5; ++i)
			{
				list[i].on_input(msg);
			}
		}
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case 0x45:
				scene_manager.switchto(scenemanager::scenetype::walk);
				break;
			}

		}
	}
	void createtemp_vec()
	{
		temp_vec.clear();
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if(!(temp_board[i][j] == 0))
				{
					std::vector<int> new_vec(3);
					new_vec[0] = i;
					new_vec[1] = j;
					new_vec[2] = temp_board[i][j];
					temp_vec.push_back(new_vec);
				}
			}
		}
	}
	void on_exit()
	{
		if (hasPuzzle)
		{
			for (int i = 0; i < 5; ++i)
			{
				list[i].setallzero();
			}
		}
	}
public:
	std::vector<region> list{ 5 };
	std::vector<std::vector<int>> temp_vec;
	bool hasPuzzle = false;
};
