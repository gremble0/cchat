#include "connection.h"
#include "ui.h"
#include <raylib.h>
#include <stdio.h>

void DrawWindow() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "cchat");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        DrawBackground();
        DrawInputField();

        EndDrawing();
    }
}

void DrawBackground() {
    ClearBackground(BACKGROUND_COLOR);

    for (int i = 0; i < WINDOW_HEIGHT; i += CHATBOX_HEIGHT * 2)
        DrawRectangle(0, i, WINDOW_WIDTH, CHATBOX_HEIGHT, ALTERNATE_BACKGROUND_COLOR);
}

void DrawInputField() {
    static char input[BUFSIZE] = "\0";
    static int letter_count = 0;

    Rectangle input_field = {
        .x      = 0,
        .y      = WINDOW_HEIGHT - CHATBOX_HEIGHT,
        .width  = WINDOW_WIDTH,
        .height = CHATBOX_HEIGHT,
    };

    int key = GetCharPressed();

    while (key > 0) {
        input[letter_count] = (char)key;
        input[letter_count + 1] = '\0';
        ++letter_count;

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        --letter_count;
        if (letter_count < 0)
            letter_count = 0;
        input[letter_count] = '\0';
    }

    DrawRectangleRec(input_field, LIGHTGRAY);

    DrawRectangleLines((int)input_field.x, (int)input_field.y, (int)input_field.width, (int)input_field.height, RED);

    DrawText(input, (int)input_field.x + 5, (int)input_field.y + 8, 40, MAROON);
    /* DrawText(TextFormat(const char *text, ...), int posX, int posY, int fontSize, Color color) */
}

void DrawNewMessage() {

}
