#ifndef RENDERER_HPP
#define RENDERER_HPP

#include<windows.h>
#include "Point.hpp"
#include "Texture.hpp"
namespace MEOM
{
class Renderer
{
public:
    ~Renderer(){}
	void drawTexture(const Texture& texture,Point it)
	{
		texture.renderTextureOnDc(bufferDc,it);
	}
	void initialize(HWND hwnd)
	{
		windowDc = GetDC(hwnd);
		bufferDc = CreateCompatibleDC(windowDc);
	}
	static Renderer* getInstance()
	{
		if (render == nullptr)
			render = new Renderer;
		return render;
	}
private:
	Renderer(){};
	RECT windowSize;
	HBITMAP bufferBitmap;
	HDC bufferDc,windowDc;
	static Renderer* render;
};
}
#endif // RENDERER_HPP
