#pragma once
#include<graphics.h>
#include<iostream>
#include<vector>
#include"boardbutton.h"
extern int board_data[5][5];

class region
{
public:
	struct han_lie_number
	{
		int han;
		int lie;
		int number;
	};

	void enter(int ha,int li,int num)
	{
		for (int i=0;i<5;++i)
		{
			if (han_lies[i].han == ha && han_lies[i].lie == li)
			{
				han_lies[i].number = num;
				buttons[i].set_num(num);
				board_data[ha][li] = num;
			}
			
		}
	}
	void init_numbers(const int(&data)[5][5]) {
		for (int i = 0; i < 5; ++i) {
			int han = han_lies[i].han;
			int lie = han_lies[i].lie;
			han_lies[i].number = data[han][lie];
			buttons[i].set_num(data[han][lie]);
		}
	}

	void setregion(int a, int b, int c, int d, int e)
	{
		width_lines.clear();
		height_lines.clear();
		outside_lines.clear();
		buttons.clear();
		is_full = false;
		deal(a, 0);
		deal(b, 1);
		deal(c, 2);
		deal(d, 3);
		deal(e, 4);
		for (int i = 0; i <5 ; ++i)
		{
			lin top_line, bottom_line, left_line, right_line;
			top_line.first = { rect_lists[i].left,rect_lists[i].top};
			top_line.second = { rect_lists[i].right,rect_lists[i].top };
			bottom_line.first = { rect_lists[i].left,rect_lists[i].bottom };
			bottom_line.second = { rect_lists[i].right,rect_lists[i].bottom };
			width_lines.push_back(top_line);
			width_lines.push_back(bottom_line);
			left_line.first = { rect_lists[i].left,rect_lists[i].top };
			left_line.second = { rect_lists[i].left,rect_lists[i].bottom };
			right_line.first = { rect_lists[i].right,rect_lists[i].top };
			right_line.second = { rect_lists[i].right,rect_lists[i].bottom };
			height_lines.push_back(left_line);
			height_lines.push_back(right_line);
		}
		createoutsides();
		for (int i = 0; i < 5; ++i)
		{
			boardbutton boardbutt(rect_lists[i],i, han_lies[i].han,han_lies[i].lie,0);

			buttons.push_back(boardbutt);
		} 
	}

	~region() = default;
	void deal(int m,int i)
	{
		int n = (m - 1) / 5; 
		int j = (m - 1) % 5; 
		rect_lists[i].left = 340 + j * 120;
		rect_lists[i].right = 340 + (j + 1) * 120;
		rect_lists[i].top = 20 + n * 120;
		rect_lists[i].bottom = 20 + (n + 1) * 120;
		han_lies[i].han = n;
		han_lies[i].lie = j;
	}
	
	struct lin
	{
		POINT first;
		POINT second;
		bool operator==(const lin& other)const
		{
			return (
				(first.x == other.first.x && first.y == other.first.y &&
					second.x == other.second.x && second.y == other.second.y)
				||
				(first.x == other.second.x && first.y == other.second.y &&
					second.x == other.first.x && second.y == other.first.y)
				);
		}
	};

	void add_unique_lines(const std::vector<lin>& source, std::vector<lin>& dest) {
		for (size_t i = 0; i < source.size(); ++i) {
			bool isUnique = true;
			
			for (size_t j = 0; j < source.size(); ++j) {
				if (i != j && source[i] == source[j]) {
					isUnique = false;
					break; 
				}
			}
			if (isUnique) {
				dest.push_back(source[i]);
			}
		}
	}

	void createoutsides() {
		outside_lines.clear(); 

		
		add_unique_lines(std::vector<lin>(width_lines.begin(), width_lines.begin() + 10), outside_lines);

		
		add_unique_lines(std::vector<lin>(height_lines.begin(), height_lines.begin() + 10), outside_lines);
	}
	void on_draw()
	{
		setlinestyle(PS_SOLID, 3);
		setlinecolor(BLACK);
		for (auto& item : outside_lines)
		{
			line(item.first.x, item.first.y, item.second.x, item.second.y);
		}
		for (int i = 0; i < 5; i++)
		{
			buttons[i].fill_color();
		}

	}
	
	
	void on_input(const ExMessage msg)
	{
		for (int i = 0; i < 5; i++)
		{
			buttons[i].processevent(msg);
		}
	}

	void on_update(int delta)
	{
		for (int i = 0; i < 5; i++)
		{
			buttons[i].on_update(delta);
		
	}
		
		
		if (ifexist(1) && ifexist(2) && ifexist(3) && ifexist(3) && ifexist(4) && ifexist(5))
		{
			
			is_full = true;
		}
		else {
			is_full = false;
		}
	}
	bool ifexist(int num)
	{
		
		for (int i = 0; i < 5; i++)
		{
			if (buttons[i].returnnum() == num)
				return true;
		}
		return false;
	}
	bool returnfull()
	{
		return is_full;
	}
	void setallzero()
	{
		for (int i = 0; i < 5; i++)
		{
			buttons[i].set_num(0);
		}
		is_full = false;
	}
private:
	std::vector<RECT> rect_lists{5};
	std::vector<lin> width_lines{};
	std::vector<lin> height_lines{};
	std::vector<lin> outside_lines;
	std::vector<han_lie_number> han_lies{ 5 };
	std::vector<boardbutton> buttons;
private:
	bool is_full = false;
};
