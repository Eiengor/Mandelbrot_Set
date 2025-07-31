#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <GLFW/glfw3.h>
#include <vector>
#include <chrono>
#include <numeric>
#include <iostream>

using namespace std;

class Performance
{
private:
	//Time
	float last_time = 0.0f;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	int time_stopper = 0;
	chrono::steady_clock::time_point start_time;

	//FPS
	vector<float> fpsHistory;
	int fCounter = 0;
	int num_frames = 0;

public:
	void startTime();
	double getStartupDuration();
	void getTime();

	void setCurrentFrameTime();
	float getFPS();
	float getAndSaveFPS();
	void cleanFPSHistory();
	float getAverageFPS();
	
	void FPSToText();
	void StartupDurationToText();
};

#endif PERFORMANCE_H