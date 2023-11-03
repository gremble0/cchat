#include <stdio.h>

#include <raylib.h>

#define WINDOW_WIDTH            400
#define WINDOW_HEIGHT           700
#define BACKGROUND_COLOR        GetColor(0x151515ff)
#define HEADER_BACKGROUND_COLOR GetColor(0x191919ff)

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "gochat");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawRectangle(0, 0, WINDOW_WIDTH, 40, HEADER_BACKGROUND_COLOR);
        EndDrawing();
    }

    return 0;
}
