#ifndef APPLICATION_H
#define APPLICATION_H

struct GLFWwindow;

class Application
{
private:
	GLFWwindow* window;
	int screenWidth, screenHeight;
	const char* title;

public:
	Application(int screenWidth = 1600, int screenHeight = 900, const char* title = "Application");
	~Application();

	bool initialize();
	bool createWindow();
	
	void beginFrame();
	void endFrame();
	void clear();

	bool shouldClose() const;
	void setShouldClose(bool shouldClose);

	GLFWwindow* getWindow();
	int getWidth();
	int getHeight();
	const char* getTitle();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void onFramebufferResize(int width, int height);

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
};

#endif // !APPLICATION_H

