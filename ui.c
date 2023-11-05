#include "ui.h"
#include <raylib.h>
#include <stdio.h>

void DrawWindow(tcp_io_params *p) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "cchat");
    SetTargetFPS(10);

    while (!WindowShouldClose()) {
        BeginDrawing();

        DrawBackground();
        DrawInputField(p);

        EndDrawing();
    }
}

void DrawBackground() {
    ClearBackground(BACKGROUND_COLOR);

    for (int i = 0; i < WINDOW_HEIGHT; i += CHATBOX_HEIGHT * 2)
        DrawRectangle(0, i, WINDOW_WIDTH, CHATBOX_HEIGHT, SECONDARY_BACKGROUND_COLOR);
}

void DrawInputField(tcp_io_params *p) {
    /* static char input[BUFSIZE] = "\0"; */
    static int letter_count = 0;

    Rectangle input_field = {
        .x      = 0,
        .y      = WINDOW_HEIGHT - CHATBOX_HEIGHT,
        .width  = WINDOW_WIDTH,
        .height = CHATBOX_HEIGHT,
    };

    int key = GetCharPressed();

    while (key > 0) {
        p->write_buf[letter_count] = (char)key;
        p->write_buf[letter_count + 1] = '\0';
        ++letter_count;

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        --letter_count;
        if (letter_count < 0)
            letter_count = 0;
        p->write_buf[letter_count] = '\0';
    }

    if (IsKeyPressed(KEY_ENTER)) {
        tcp_write(p->serverfd, p->write_buf, strlen(p->write_buf) + 1);
        p->write_buf = "";
    }

    DrawRectangleRec(input_field, TERTIARY_BACKGROUND_COLOR);

    DrawRectangleLines((int)input_field.x, (int)input_field.y, (int)input_field.width, (int)input_field.height, GOLD_YELLOW);

    DrawText(p->write_buf, (int)input_field.x + 5, (int)input_field.y + 8, 40, FONT_COLOR);
}

void DrawNewMessage() {

}
