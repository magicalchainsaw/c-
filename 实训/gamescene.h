#pragma once
#include"scenemanager.h"
#include"region.h"
#include<graphics.h>
#include <tchar.h>
#include"scenemanager.h"
const int puzzle_length = 600;
extern int board_data[5][5];
extern int score;
extern scenemanager scene_manager;
class game_scene_1 :public scene
{
public:
	game_scene_1() = default;
	~game_scene_1() {}
	void on_enter() {
		setbkcolor(RGB(173, 216, 230));
		settextcolor(WHITE);
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
				board_data[i][j] = 0;
		}
		settextcolor(WHITE);
		list[0].setregion(1, 2, 3, 4, 8);
		list[1].setregion(5, 10, 15, 20, 25);
		list[2].setregion(6, 7, 11, 12, 16);
		list[3].setregion(13, 17, 18, 21, 22);
		list[4].setregion(9, 14, 19, 23, 24);
		for (int i=0;i<5;++i)
		{
			list[i].enter(0, 4, 4);
			list[i].enter(1, 1, 5);
			list[i].enter(1, 3, 2);
			list[i].enter(2, 2, 3);
			list[i].enter(3, 1, 1);
			list[i].enter(3, 3, 5);
			list[i].enter(4, 0, 5);
		}
	}
	void on_update(int delta) {
		for (int i = 0; i < 5; ++i)
		{
			list[i].enter(0, 4, 4);
			list[i].enter(1, 1, 5);
			list[i].enter(1, 3, 2);
			list[i].enter(2, 2, 3);
			list[i].enter(3, 1, 1);
			list[i].enter(3, 3, 5);
			list[i].enter(4, 0, 5);
		}
		for (int i = 0; i < 5; i++)
		{
			list[i].on_update(delta);
		}
		if (is_board_true() && is_all_region_full())
		{
			score =score+10;
			scene_manager.switchto(scenemanager::scenetype::walk);
		}

	
	}
	void on_exit()
	{
		for (int i = 0; i < 5; ++i)
		{
			list[i].setallzero();
		}
	}
	void on_draw() { 
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		for (int i = 0;i<6;i++)
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
					outtextxy(340 + 120 * j+(120-textwidth(str))/2, 20 + 120 * i+(120-textheight(str))/2, str);
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
		for (int i = 0; i < 5; ++i)
		{
			list[i].on_input(msg);
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
	
private:
	std::vector<region> list{ 5 };

};
class game_scene_2 :public scene
{
public:
	game_scene_2() = default;
	~game_scene_2() {}
	void on_enter() {
		settextcolor(WHITE);
		setbkcolor(RGB(173, 216, 230));
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
				board_data[i][j] = 0;
		}
		list[0].setregion(1, 2, 7, 12, 13);
		list[1].setregion(3, 4, 5, 8, 9);
		list[2].setregion(6, 11, 16, 21, 22);
		list[3].setregion(17, 18, 23, 24, 25);
		list[4].setregion(10, 14, 15, 19, 20);
		for (int i = 0; i < 5; ++i)
		{
			list[i].enter(0, 0, 4);
			list[i].enter(1, 2, 5);
			list[i].enter(2, 1, 3);
			list[i].enter(2, 3, 1);
			list[i].enter(3, 2, 4);
			list[i].enter(4, 4, 3);
		}
	}
	void on_update(int delta) {
		for (int i = 0; i < 5; ++i)
		{
			list[i].enter(0, 0, 4);
			list[i].enter(1, 2, 5);
			list[i].enter(2, 1, 3);
			list[i].enter(2, 3, 1);
			list[i].enter(3, 2, 4);
			list[i].enter(4, 4, 3);
		}
		for (int i = 0; i < 5; i++)
		{
			list[i].on_update(delta);
		}
		if (is_board_true() && is_all_region_full())
		{
			score += 10;
			scene_manager.switchto(scenemanager::scenetype::walk);
		}

	}
	void on_draw() {
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
		for (int i = 0; i < 5; ++i)
		{
			list[i].on_input(msg);
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
	void on_exit() {
		for (int i = 0; i < 5; ++i)
		{
			list[i].setallzero();
		}
	}
private:
	std::vector<region> list{ 5 };

};
class game_scene_3 :public scene
{
public:
	game_scene_3() = default;
	~game_scene_3() {}
	void on_enter() {
		settextcolor(WHITE);
		setbkcolor(RGB(173, 216, 230));
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
				board_data[i][j] = 0;
		}
		list[0].setregion(1, 2, 3, 4, 6);
		list[1].setregion(5, 8, 9, 10, 15);
		list[2].setregion(7, 11, 12, 13, 17);
		list[3].setregion(16, 18, 21, 22, 23);
		list[4].setregion(14, 19, 20, 24, 25);
		for (int i = 0; i < 5; ++i)
		{
			list[i].enter(0, 0, 4);
			list[i].enter(0, 1, 1);
			list[i].enter(0, 4, 5);
			list[i].enter(1, 1, 4);
			list[i].enter(3, 3, 3);
			list[i].enter(4, 0, 2);
			list[i].enter(4, 3, 4);
			list[i].enter(4, 4, 1);
		}
	}
	void on_update(int delta) {
		for (int i = 0; i < 5; ++i)
		{
			list[i].enter(0, 0, 4);
			list[i].enter(0, 1, 1);
			list[i].enter(0, 4, 5);
			list[i].enter(1, 1, 4);
			list[i].enter(3, 3, 3);
			list[i].enter(4, 0, 2);
			list[i].enter(4, 3, 4);
			list[i].enter(4, 4, 1);
		}
		for (int i = 0; i < 5; i++)
		{
			list[i].on_update(delta);
		}
		if (is_board_true() && is_all_region_full())
		{
			score += 10;
			scene_manager.switchto(scenemanager::scenetype::walk);
		}

	}
	void on_draw() {
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
		for (int i = 0; i < 5; ++i)
		{
			list[i].on_input(msg);
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
	void on_exit() {
		for (int i = 0; i < 5; ++i)
		{
			list[i].setallzero();
		}
	}
private:
	std::vector<region> list{ 5 };

};
