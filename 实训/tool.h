#pragma once
#pragma once
#include<graphics.h>
#pragma comment(lib,"MSIMG32.LIB")
#pragma comment(lib,"Winmm")


inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void putimage_alpha(int x, int y, int width, int height, IMAGE* img, int src_x, int src_y)
{
	int w = width > 0 ? width : img->getwidth();
	int h = height > 0 ? height : img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void flip_image(IMAGE* ori, IMAGE* res)
{
	int w = ori->getwidth();
	int h = ori->getheight();
	Resize(res, w, h);
	DWORD* buffer1 = GetImageBuffer(ori);
	DWORD* buffer2 = GetImageBuffer(res);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int ori_num = y * w + x;
			int src_num = y * w + (w - x - 1);
			buffer2[src_num] = buffer1[ori_num];
		}
	}
}