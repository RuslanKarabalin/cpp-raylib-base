#include <raylib.h>

static int WINDOW_WIDTH = 1600;
static int WINDOW_HEIGHT = 900;

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "WindowName");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        int textX = WINDOW_WIDTH / 2;
        int textY = WINDOW_HEIGHT / 2;
        DrawText("Text in window", textX, textY, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
