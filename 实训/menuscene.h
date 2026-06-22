#pragma once
#include"button.h"
#include "scene.h"
#include <iostream>
#include "scenemanager.h"
#include<graphics.h>
extern IMAGE img_title;
extern scenemanager scene_manager;
extern bool running;
extern RECT region_start, region_quit;
startbutton stabutton;
quitbutton quibutton;

class menu_scene :public scene
{
public:
	menu_scene() {}
	~menu_scene() {}
	void on_enter(
	) {
		stabutton.setbutton(region_start, _T("resources/ui_start_idle.png"), _T("resources/ui_start_hovered.png"), _T("resources/ui_start_pushed.png"));
		quibutton.setbutton(region_quit, _T("resources/ui_quit_idle.png"), _T("resources/ui_quit_hovered.png"), _T("resources/ui_quit_pushed.png"));
		

	}
	void on_update(int delta) {
		
	}
	void on_draw() {
		stabutton.draw();
		quibutton.draw();
		putimage((1280-img_title.getwidth())/2, 100, &img_title);
	}
	void on_input(const ExMessage msg) {
		stabutton.processevent(msg);
		quibutton.processevent(msg);
		
	}
	void on_exit() {

	}
private:
	
	
};