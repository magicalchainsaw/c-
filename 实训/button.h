#pragma once
#include<graphics.h>
#include"scenemanager.h"

extern bool running;
extern scenemanager scene_manager;

class button
{
public:
	button() = default;
	void setbutton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
	{
		region = rect;
		loadimage(&img_idle, path_img_idle);
		loadimage(&img_hovered, path_img_hovered);
		loadimage(&img_pushed, path_img_pushed);
	}

	~button() = default;
	virtual void draw()
	{
		switch (status)
		{
		case Status::idle:
			putimage(region.left, region.top, &img_idle);
			break;
		case Status::hovered:
			putimage(region.left, region.top, &img_hovered);
			break;
		case Status::pushed:
			putimage(region.left, region.top, &img_pushed);
			break;
		}
	}
	void processevent(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			if (status == Status::idle && checkhit(msg.x, msg.y))
				status = Status::hovered;
			else if (status == Status::hovered && !checkhit(msg.x, msg.y))
				status = Status::idle;
			break;
		case WM_LBUTTONDOWN:
			if (checkhit(msg.x, msg.y))
				status = Status::pushed;
			break;
		case WM_LBUTTONUP:
			if (status == Status::pushed)
				OnClick();
			break;
		}
	}
protected:
	virtual void OnClick() = 0;
private:
	enum class Status {
		idle = 0, hovered, pushed
	};
private:
	RECT region;
	IMAGE img_idle;
	IMAGE img_hovered;
	IMAGE img_pushed;
	Status status = Status::idle;
private:
	bool checkhit(int x, int y)
	{
		return x >= region.left && x <= region.right && y >= region.top && y <= region.bottom;
	}

};

class quitbutton :public button
{
public:
	  ~quitbutton() = default;
protected:
	void OnClick()
	{
		running = false;
	}
};
class startbutton :public button
{
public:
	  ~startbutton() = default;
protected:
	void OnClick()
	{
		scene_manager.switchto(scenemanager::scenetype::walk);
		
	}
};
