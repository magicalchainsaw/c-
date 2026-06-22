#pragma once
#include<graphics.h>
#include"animation.h"
#include"vector2.h"
#include"platform.h"
#include"portal.h"
extern Atlas atlas_mushrooms_idle_left;
extern Atlas atlas_mushrooms_idle_right;
extern Atlas atlas_mushrooms_run_left;
extern Atlas atlas_mushrooms_run_right;
extern std::vector<platform> platform_list;
extern std::vector<portal> portal_list;
extern scenemanager scene_manager;
class player {
public:
	player()
	{
		current_anime = &idle_right;
		run_left.set_atlas(&atlas_mushrooms_run_left);
		run_right.set_atlas(&atlas_mushrooms_run_right);
		idle_left.set_atlas(&atlas_mushrooms_idle_left);
		idle_right.set_atlas(&atlas_mushrooms_idle_right);
		run_left.set_interval(75);
		run_right.set_interval(75);
		idle_left.set_interval(75);
		idle_right.set_interval(75);
		size.x = 96;
		size.y = 96;
	}
	~player() = default;
	void on_update(int delta)
	{
		int direction = is_right_key_down - is_left_key_down;
		if (direction != 0)
		{
			facing_right = direction > 0;
			current_anime = facing_right ? &run_right : &run_left;
			float distance = run_speed * delta * direction;
			on_run(distance);
		}
		else
		{
			current_anime=facing_right ? &idle_right : &idle_left;
		}
		current_anime->on_update(delta);
		move_coll(delta);
		
	}
	void on_input(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
			case 0x41:
				is_left_key_down = true;
				break;
			case 0x44:
				is_right_key_down = true;
				break;
			case 0x57:
				on_jump();
				break;
			case 0x45:
				switchscene();
				coutpoint();
				break;
			}
			break;
		case WM_KEYUP:
			switch (msg.vkcode)
			{
			case 0x41:
				is_left_key_down = false;
				break;
			case 0x44:
				is_right_key_down = false;
				break;
			}
			break;
		}
	}

	void on_draw()
	{
		current_anime->on_draw((int)pos.x, (int)pos.y);
	}
	void on_run(float distance)
	{
		pos.x += distance;
	}
	void on_jump()
	{
		if (speed.y != 0)
			return;
		speed.y += jump_speed;
	}
	void set_position(float x, float y)
	{
		pos.x = x;
		pos.y = y;
	}
	void move_coll(int delta)
	{
		speed.y += gravity * delta;
		pos += speed * (float)delta;
		if (speed.y > 0)
		{
			for (const platform& platform : platform_list)
			{
				const platform::collisionshape& shape = platform.shape;
				bool is_coll_x = (max(pos.x + size.x, shape.right) - min(pos.x, shape.left) <= size.x + (shape.right - shape.left));
				bool is_coll_y = (shape.y >= pos.y && shape.y <= pos.y + size.y);
				if (is_coll_x && is_coll_y)
				{
					float last_tick_y = pos.y + size.y - (float)(delta * speed.y);
					if (last_tick_y <= shape.y)
					{
						pos.y = shape.y - size.y;
						speed.y = 0;
						break;
					}
				}
			}

		}

	}
	void switchscene()
	{
		for (int i = 0; i < 4; i++)
		{
			bool is_coll_x = (max(pos.x + size.x, portal_list[i].posi.x + 35 + portal_list[i].size.x) - min(pos.x, portal_list[i].posi.x + 35) <= size.x + portal_list[i].size.x);
			bool is_coll_y = ((portal_list[i].posi.y + portal_list[i].size.y >= pos.y + size.y) && (portal_list[i].posi.y <= pos.y));
			if (is_coll_x && is_coll_y)
			{
				switch (i)
				{
				case 0:
					scene_manager.switchto(scenemanager::scenetype::game_1);
					break;
				case 1:
					scene_manager.switchto(scenemanager::scenetype::game_2);
					break;
				case 2:
					scene_manager.switchto(scenemanager::scenetype::game_3);
					break;
				case 3:
					scene_manager.switchto(scenemanager::scenetype::game_made);
					break;
				}
			}
		}
		
			
		
	}

	void coutpoint()
	{
		std::cout << returnx() << " " << returny();
	}
	float returny()
	{
		return pos.y;
	}
	float returnx()
	{
		return pos.x;
	}
	void setspeedzero()
	{
		speed.x = 0;
		speed.y = 0;
	}
	void setboolfalse()
	{
	 is_left_key_down = false;
     is_right_key_down = false;
     facing_right = false;
	}
private:
	const float run_speed = 0.55f;
	float gravity = 1.6e-3f;
	const float jump_speed = -0.75f;
	vector2 pos;
	vector2 size;
	vector2 speed;
	Animation run_left;
	Animation run_right;
	Animation idle_left;
	Animation idle_right;
	Animation* current_anime = nullptr;
	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool facing_right = false;
};