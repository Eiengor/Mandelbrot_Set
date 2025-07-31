#include "Performance.h"
using namespace std;

void Performance::startTime()
{
	start_time = chrono::high_resolution_clock::now();
}

void Performance::getTime()
{
	last_time = glfwGetTime();
}

double Performance::getStartupDuration()
{
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> startup_duration = end_time - start_time;
    time_stopper = 1;
    return startup_duration.count();
}

void Performance::setCurrentFrameTime()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

float Performance::getFPS()
{
    float fps = 1.0f / deltaTime;
    return fps;
}

float Performance::getAndSaveFPS()
{
    float fps = 1.0f / deltaTime;
    fpsHistory.push_back(fps);
    return fps;
}

void Performance::cleanFPSHistory()
{
    fpsHistory.clear();
    fpsHistory.shrink_to_fit();
}

float Performance::getAverageFPS()
{
    if (!fpsHistory.empty()) {
        float sum = accumulate(fpsHistory.begin(), fpsHistory.end(), 0.0f);
        float avgFps = sum / fpsHistory.size();
        return avgFps;
    }
}

void Performance::FPSToText()
{
    if (fCounter > 100) {
        cout << "FPS: " << fpsHistory.back() << endl;
        fCounter = 0;
    }
    else {
        fCounter++;
    }
}

void Performance::StartupDurationToText()
{
    if (time_stopper == 0)
    {
        cout << "Startup time: " << getStartupDuration() << " seconds" << endl;
    }
}