#pragma once
#include<graphics.h>
#include"scene.h"


extern scene* menuscene;
extern scene* walkscene;
extern scene* gamescene_1;
extern scene* gamescene_2;
extern scene* gamescene_3;
extern scene* givepuzzle;
extern scene* game_made_0;
extern scene* rank_;
class scenemanager {

public:
	scenemanager() = default;
	~scenemanager() = default;
	enum scenetype
	{
		menu, walk, game_1, game_2, game_3, give, game_made,rank
	};
	void setcurrentscene(scene* scene)
	{
		currentscene = scene;
		currentscene->on_enter();
	}
	void switchto(scenetype type)
	{
		currentscene->on_exit();
		switch (type)
		{
		case scenetype::menu:
			currentscene = menuscene;
			break;
		case scenetype::walk:
			currentscene = walkscene;
			break;
		case scenetype::game_1:
			currentscene = gamescene_1;
			break;
		case scenetype::game_2:
			currentscene = gamescene_2;
			break;
		case scenetype::game_3:
			currentscene = gamescene_3;
			break;
		case scenetype::give:
			currentscene =givepuzzle ;
			break;
		case scenetype::game_made:
			currentscene = game_made_0;
			break;
		case scenetype::rank:
			currentscene = rank_;
			break;
		default:
			break;

		}
		currentscene->on_enter();
	}
	void on_update(int delta)
	{
		currentscene->on_update(delta);
	}
	void on_draw()
	{
		currentscene->on_draw();
	}
	void on_input(const ExMessage& msg)
	{
		currentscene->on_input(msg);
	}
private:
	scene* currentscene = nullptr;
};