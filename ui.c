#include "ui.h"
#include <raylib.h>

void DrawWindow() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "cchat");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        int font_offset = 20;
        for (int i = 0; i < WINDOW_HEIGHT; i += CHATBOX_HEIGHT * 2)
            DrawRectangle(0, i, WINDOW_WIDTH, CHATBOX_HEIGHT, ALTERNATE_BACKGROUND_COLOR);

        /* TODO: Change to DrawTextEx to change font */
        /* DrawText("yo", font_offset, i, FONT_SIZE, FONT_COLOR); */

        EndDrawing();
    }
}

void DrawNewMessage() {

}
