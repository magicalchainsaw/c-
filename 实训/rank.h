#pragma once
#include<iostream>
#include"scene.h"
#include<string>
#include<vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include<graphics.h>
#include <chrono>
extern int score;
extern DWORD all_time;
class rank:public scene {
public:
	struct record {
		
		int score_0;
		int time; 
		int ranking;
	};

	void on_enter()
	{
		setbkcolor(BLACK);
		current_record.score_0 = score;
		current_record.time = (int)(all_time)/1000;
		record_list.clear();
		std::ifstream file("rank.txt");
		std::string line;
		while (std::getline(file, line))
		{
			int score_, time_, ranking_;
			std::istringstream iss(line);
			iss >> ranking_ >> score_ >> time_;
			record temprecord;
			temprecord.ranking = ranking_;
			temprecord.score_0 = score_;
			temprecord.time = time_;
			record_list.push_back(temprecord);
		}
		current_record.ranking = record_list.size() + 1;
		record_list.push_back(current_record);
		std::sort(record_list.begin(), record_list.end(), [](record a, record b) {
			return a.score_0 > b.score_0;
			});
		for (int i = 0; i < record_list.size(); i++)
		{
			record_list[i].ranking = i;
		}
		settextstyle(20, 0, 0);
	}
	void out()
	{
		std::ofstream file("rank.txt");
		for (int i = 0; i < record_list.size(); i++)
		{
			file << record_list[i].ranking << " " << record_list[i].score_0 << " " << record_list[i].time << std::endl;
		}
		file.close();
	}
	
	void on_draw()
	{
		for (auto itr : record_list)
		{
			std::cout << itr.ranking << " " << itr.score_0 << " " << itr.time << std::endl;
		}
		settextstyle(30, 0, _T("Arial"));
		outtextxy(320, 100, _T("ranking"));
		outtextxy(640, 100, _T("score"));
		outtextxy(960, 100, _T("time"));
		settextstyle(20, 0, _T("Arial"));
		for (int i = 0; i < record_list.size(); i++)
		{
			TCHAR rank_1[64];
			TCHAR score_1[64];
			TCHAR time_1[64];
			_stprintf_s(rank_1, _T(" %d"),i+1);
			_stprintf_s(score_1, _T(" %d"),record_list[i].score_0);
			_stprintf_s(time_1, _T(" %d"), record_list[i].time);
			outtextxy(320, 150 + 60 * i, rank_1);
			outtextxy(640, 150+60*i, score_1);
			outtextxy(960, 150+60*i, time_1);
		}
	}
	void on_update()
	{

	}
	void on_input(const ExMessage msg) {
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case 0x09:
				scene_manager.switchto(scenemanager::scenetype::walk);
				break;
			case 0x45:
				scene_manager.switchto(scenemanager::scenetype::walk);
				record_already = true;
				break;
			}

		}
	}
	void on_exit()
	{

		if (record_already == true)
		{
			out();
			record_already = false;
		}
		record_list.clear();
	}
private:
	std::vector<record> record_list;
	record current_record;
	bool record_already = false;
	};