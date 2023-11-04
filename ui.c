#include "ui.h"

void DrawWindow() {
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);
    DrawRectangle(0, 0, WINDOW_WIDTH, 40, HEADER_BACKGROUND_COLOR);
    EndDrawing();
}
