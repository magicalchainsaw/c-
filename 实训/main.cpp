#include<iostream>
#include<graphics.h>
#include"tool.h"
#include"atlas.h"
#include"scene.h"
#include"animation.h"
#include"scenemanager.h"
#include"menuscene.h"
#include"walkscene.h"
#include"gamescene.h"
#include"button.h"
#include"platform.h"
#include"givepuzzle.h"
#include"game_made.h"
#include"rank.h"
std::vector<std::vector<int>> vec;
std::vector<std::vector<int>> vec1;
int temp_board[5][5]={};
int board_data[5][5] = {};
DWORD all_time=0;
const int window_width = 1280;
const int window_height = 640;
const int botton_width = 192;
const int botton_height = 75;
scene* menuscene=nullptr;
scene* walkscene=nullptr;
scene* gamescene_1 = nullptr;
scene* gamescene_2 = nullptr;
scene* gamescene_3 = nullptr;
scene* givepuzzle = nullptr;
scene* game_made_0 = nullptr;
scene* rank_ = nullptr;
scenemanager scene_manager;
std::vector<platform> platform_list;
std::vector<portal> portal_list;
bool running = true;
int score = 0;
RECT region_start, region_quit;
void initRegions() {

	region_start.left = (window_width - botton_width) / 2;
	region_start.right = region_start.left + botton_width;
	region_start.top = 430;
	region_start.bottom = region_start.top + botton_height;

	region_quit.left = (window_width - botton_width) / 2;
	region_quit.right = region_quit.left + botton_width;
	region_quit.top = 550;
	region_quit.bottom = region_quit.top + botton_height;
}

void flip_atlas(Atlas& ori, Atlas& res)
{
	res.clear();
	for (int i = 0; i < ori.getsize(); ++i)
	{
		IMAGE aft;
		flip_image(ori.get_image(i), &aft);
		res.addimage(aft);
	}
}
IMAGE img_title;
IMAGE img_sky; 
IMAGE img_hills; 
IMAGE img_platform_large; 
IMAGE img_platform_small; 
IMAGE img_bridge;
Atlas atlas_mushrooms_idle_left; 
Atlas atlas_mushrooms_idle_right; 
Atlas atlas_mushrooms_run_left;
Atlas atlas_mushrooms_run_right;
Animation anime_idle_left;
Animation anime_idle_right;
Animation anime_run_left;
Animation anime_run_right;
Atlas portal_atlas;
void load_game_sources()
{
	atlas_mushrooms_idle_left.load_from_file(_T("resources/Mushroom-Idle_%d.png"), 6);
	atlas_mushrooms_run_left.load_from_file(_T("resources/Mushroom-Run_%d.png"), 8);
	portal_atlas.load_from_file(_T("resources/split_%d.png"), 6);
	flip_atlas(atlas_mushrooms_idle_left, atlas_mushrooms_idle_right);
	flip_atlas(atlas_mushrooms_run_left, atlas_mushrooms_run_right);
	loadimage(&img_sky, _T("resources/sky.png"));
	loadimage(&img_hills, _T("resources/hills.png"));
	loadimage(&img_platform_large, _T("resources/platform_large.png"));
	loadimage(&img_platform_small, _T("resources/platform_small.png"));
	loadimage(&img_title, _T("resources/menu_1.png"));
	loadimage(&img_bridge, _T("resources/bridge.png"));
}


	

int main()
{
	ExMessage msg;
	const int fps = 60;
	initgraph(1280, 640);
	setbkcolor(RGB(0, 0, 0));
	load_game_sources();
	initRegions();
	menuscene = new menu_scene();
	walkscene = new walk_scene();
	gamescene_1 = new game_scene_1();
	gamescene_2 = new game_scene_2();
	gamescene_3 = new game_scene_3();
	givepuzzle = new give_scene();
	game_made_0 = new game_made();
	rank_ = new rank();
	scene_manager.setcurrentscene(menuscene);
	BeginBatchDraw();
	while (running)
	{
		DWORD frame_start_time = GetTickCount();
		while (peekmessage(&msg))
		{
			scene_manager.on_input(msg);
		}
		static DWORD last_tick_time = GetTickCount();
		DWORD now_tick_time = GetTickCount();
		DWORD delta_tick = now_tick_time - last_tick_time;
		
		scene_manager.on_update(delta_tick);
		last_tick_time = now_tick_time;
		cleardevice();
		scene_manager.on_draw();
	
		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta = frame_end_time - frame_start_time;
		if (frame_delta < 1000 / fps)
		{
			Sleep(1000 / fps - frame_delta);
		}
		all_time = all_time + 1000 / fps;
	}
	EndBatchDraw();
}
