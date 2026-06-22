#pragma once


#include<graphics.h>
#include"tool.h"
#include"platform.h"
#include"player.h"
#include"portal.h"
#include<vector>
extern IMAGE img_sky;
extern IMAGE img_hills;
extern IMAGE img_platform_large;
extern IMAGE img_platform_small;
extern std::vector<platform> platform_list;
extern std::vector<portal> portal_list;
extern int score;
extern IMAGE img_bridge;
extern scenemanager scene_manager;
class walk_scene :public scene
{
public:
	walk_scene() {}
	~walk_scene() {}
	void on_enter() {
		pos_img_hills.x = (getwidth() - img_hills.getwidth()) / 2;
		pos_img_hills.y = (getheight() - img_hills.getheight()) / 2;
		pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
		pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;
		
		platform_list.resize(4);
		platform& large_platform = platform_list[0];
		large_platform.img = &img_platform_large;
		large_platform.render_position.x = 122;
		large_platform.render_position.y = 455;
		large_platform.shape.left = (float)large_platform.render_position.x + 30;
		large_platform.shape.right = 1280;
		large_platform.shape.y = (float)large_platform.render_position.y + 60;
		platform& small_platform_1 = platform_list[1];
		small_platform_1.img = &img_platform_small;
		small_platform_1.render_position.x = 175;
		small_platform_1.render_position.y = 360;
		small_platform_1.shape.left = (float)small_platform_1.render_position.x + 40;
		small_platform_1.shape.right = (float)small_platform_1.render_position.x + img_platform_small.getwidth() - 40;
		small_platform_1.shape.y = (float)small_platform_1.render_position.y + img_platform_small.getheight() / 2;

		platform& small_platform_2 = platform_list[2];
		small_platform_2.img = &img_platform_small;
		small_platform_2.render_position.x = 855;
		small_platform_2.render_position.y = 360;
		small_platform_2.shape.left = (float)small_platform_2.render_position.x + 40;
		small_platform_2.shape.right = (float)small_platform_2.render_position.x + img_platform_small.getwidth() - 40;
		small_platform_2.shape.y = (float)small_platform_2.render_position.y + img_platform_small.getheight() / 2;

		platform& small_platform_3 = platform_list[3];
		small_platform_3.img = &img_platform_small;
		small_platform_3.render_position.x = 515;
		small_platform_3.render_position.y = 225;
		small_platform_3.shape.left = (float)small_platform_3.render_position.x + 40;
		small_platform_3.shape.right = (float)small_platform_3.render_position.x + img_platform_small.getwidth() - 40;
		small_platform_3.shape.y = (float)small_platform_3.render_position.y + img_platform_small.getheight() / 2;
		pos_img_bridge.x= (float)large_platform.render_position.x + img_platform_large.getwidth() - 30;
		pos_img_bridge.y = 515;
		p1.set_position(100, 100);
		p1.setspeedzero();
		portal_list.resize(4);
		portal_list[0].setposition(235, 263);
		portal_list[1].setposition(570, 128);
		portal_list[2].setposition(914, 263);
		portal_list[3].setposition(570, 399);
		
	}
	void on_update(int delta) {
		p1.on_update(delta);
		for (portal& port : portal_list)
		{
			port.on_update(delta);
		}
		if (p1.returny() > 640)
		{
			p1.set_position(300, 0);
		}
		if (p1.returnx() > 1260)
		{
			scene_manager.switchto(scenemanager::scenetype::give);
		}
	}
	void on_draw() {

		putimage_alpha(pos_img_sky.x, pos_img_sky.y, &img_sky);
		putimage_alpha(pos_img_hills.x, pos_img_hills.y, &img_hills);
		putimage_alpha(pos_img_bridge.x, pos_img_bridge.y, &img_bridge);
		drawmode();
		for (const platform& platform : platform_list)
		{
			platform.on_draw();
		}
		for ( portal& port : portal_list)
		{
			port.draw();
		}
		p1.on_draw();
		drawscore(score);

		
	}
	void on_input(const ExMessage msg) {
		p1.on_input(msg);
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case 0x09:
				scene_manager.switchto(scenemanager::scenetype::rank);
				break;
			}

		}
	}
	void on_exit() {
		p1.setboolfalse();
		p1.setspeedzero();
	}
	
	void drawmode()
	{
		settextstyle(30, 0, _T("Arial"));
		settextcolor(WHITE);
		setbkmode(TRANSPARENT);
		outtextxy(265, 233, _T("First"));
		outtextxy(590, 98, _T("Second"));
		outtextxy(944, 233, _T("Third"));

	}
	void drawscore(int scor)
	{
		static TCHAR text[64];
		_stprintf_s(text, _T("当前玩家得分为:%d"), scor);
		settextcolor(RGB(255, 85, 185));
		settextstyle(30, 0, _T("Arial"));
		outtextxy(10, 10, text);
	}
	
private:
	POINT pos_img_hills = { 0 };
	POINT pos_img_sky = { 0 };
	POINT pos_img_bridge = { 0 };
	player p1;
};