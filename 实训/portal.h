#pragma once
#include"animation.h"
#include"vector2.h"
#include"scenemanager.h"
extern Atlas portal_atlas;

class portal {
public:
	

	portal()
	{
		portal_anime.set_atlas(&portal_atlas);
		size.x = 50;
		size.y = 120;
		portal_anime.set_interval(75);
	}
	void setposition(int x, int y)
	{
		posi.x = x;
		posi.y = y;
	}
	void draw()
	{
		portal_anime.on_draw(posi.x, posi.y);
	}
	void on_update(int delta)
	{
		portal_anime.on_update(delta);
	}
	

	vector2 posi;
	vector2 size;
	Animation portal_anime;
};