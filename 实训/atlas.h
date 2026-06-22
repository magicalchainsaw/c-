#pragma once
#include<vector>
#include<graphics.h>
#include"tool.h"
class Atlas {
public:
	Atlas() = default;
	~Atlas() = default;
	void load_from_file(LPCTSTR path, int num)
	{
		img_list.clear();
		img_list.resize(num);
		TCHAR path_file[256];
		for (int i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path, i + 1);
			loadimage(&img_list[i], path_file);
		}

	}
	void clear()
	{
		img_list.clear();
	}
	int getsize()
	{
		return (int)img_list.size();
	}
	IMAGE* get_image(int dex)
	{
		if (dex<0 || dex>img_list.size())
			return nullptr;
		return &img_list[dex];
	}
	void addimage(const IMAGE img)
	{
		img_list.push_back(img);
	}

private:
	std::vector<IMAGE> img_list;
}; 
