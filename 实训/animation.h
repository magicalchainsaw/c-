#pragma once
#include<graphics.h>
#include"atlas.h"
#include"tool.h"

class Animation {
public:
	Animation() = default;
	~Animation() = default;

	void reset()
	{
		timer = 0;
		interval = 0;
	}
	void set_atlas(Atlas* atla)
	{
		reset();
		atlas = atla;
	}
	void setloop(bool flag)
	{
		is_loop = flag;
	}
	void set_interval(int ms)
	{
		interval = ms;
	}

	int getidx()
	{
		return idx_frame;
	}
	IMAGE* getframe()
	{
		return atlas->get_image(idx_frame);
	}
	bool checkfinish()
	{
		if (is_loop)return false;
		return(idx_frame == atlas->getsize() - 1);
	}
	void on_update(int delta)
	{
		timer += delta;
		if (timer >= interval)
		{
			timer = 0;
			++idx_frame;
			if (idx_frame >= atlas->getsize())
			{
				idx_frame = is_loop ? 0 : atlas->getsize() - 1;
				
			}
		}
	}
	
	void on_draw(int x, int y)const
	{
		putimage_alpha(x, y, atlas->get_image(idx_frame));
	}
private:
	Atlas* atlas = nullptr;
	int timer = 0;//计时器
	int interval = 0;//间隔
	int idx_frame = 0;//帧索引
	bool is_loop = true;
	

};