#include "Resources.h"
using namespace std;
using namespace glm;

int main() {
    try
    {
        Performance performance;
        performance.startTime();

        Application app(screen_width, screen_height, "Mandelbrot");
        Texture mandelbrotTexture(screen_width, screen_height);
        Shader displayShader("textureDisplay.vert", "textureDisplay.frag");
        ComputeShader computeShader("mandelbrotSet.comp");
        VAO vao;
        vao.Bind();
        VBO vbo(vertices, sizeof(vertices));
        EBO ebo(indices, sizeof(indices));
        vao.LinkVBO(vbo, 0);
        vao.Unbind();
        Renderer renderer(screen_width, screen_height);
        InputHandler inputHandler;
        UI ui(app, 1.5f);

        performance.getTime();
        while (!app.shouldClose())
        {
            app.beginFrame();
            performance.setCurrentFrameTime();
            inputHandler.processInput(app.getWindow(), zoom, center_x, center_y);     
            performance.getAndSaveFPS();
            performance.FPSToText();
            ui.NewFrame();
            ui.ShowWindow(zoom, center_x, center_y, performance);
            renderer.render(vao, mandelbrotTexture, displayShader, computeShader,
                zoom, center_x, center_y);
            performance.StartupDurationToText();
            ui.Render();
            app.endFrame();
        }
        cout << "Average FPS: " << performance.getAverageFPS() << endl;
        renderer.clear(vao, vbo, ebo, mandelbrotTexture, displayShader, computeShader);
        performance.cleanFPSHistory();
        ui.clear();
        app.~Application();
        return 0;
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
}