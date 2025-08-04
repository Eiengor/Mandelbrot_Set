#ifndef UI_H
#define UI_H

#include "imGui/imgui.h"
#include "imGui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h"
#include "Application.h"
#include "Performance.h"

class UI
{
public:
	UI(Application& app, int fontGlobalScale);
	void NewFrame();
	void ShowWindow(float zoom, float center_x, float center_y, Performance& performance);
	void Render();
	void clear();
};

#endif // !UI_H


