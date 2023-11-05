#include "ui.h"
#include <stdio.h>
#include <string.h>

void DrawWindow(connection *conn) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "cchat");
    SetTargetFPS(10);

    pthread_t message_thread;
    pthread_create(&message_thread, NULL, tcp_read_messages, &*conn);

    while (!WindowShouldClose()) {
        BeginDrawing();

        DrawBackground();
        // TODO: inputfield drawing on separate thread?
        DrawInputField(conn);

        for (int i = 0; i < conn->messages_len; i++)
            DrawText(conn->messages[i], 10, CHATBOX_HEIGHT * i, FONT_SIZE, GOLD_YELLOW);

        EndDrawing();
    }

    pthread_join(message_thread, NULL);
}

void DrawBackground() {
    ClearBackground(BACKGROUND_COLOR);

    for (int i = 0; i < WINDOW_HEIGHT; i += CHATBOX_HEIGHT * 2)
        DrawRectangle(0, i, WINDOW_WIDTH, CHATBOX_HEIGHT, SECONDARY_BACKGROUND_COLOR);
}

void DrawInputField(connection *conn) {
    Rectangle input_field = {
        .x      = 0,
        .y      = WINDOW_HEIGHT - CHATBOX_HEIGHT,
        .width  = WINDOW_WIDTH,
        .height = CHATBOX_HEIGHT,
    };

    int key = GetCharPressed();

    while (key > 0 && conn->write_buf_len < BUFSIZE + 1) {
        conn->write_buf[conn->write_buf_len] = (char)key;
        conn->write_buf[conn->write_buf_len + 1] = '\0';
        ++conn->write_buf_len;

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && conn->write_buf_len != 0) {
        --conn->write_buf_len;
        conn->write_buf[conn->write_buf_len] = '\0';
    }

    if (IsKeyPressed(KEY_ENTER) && conn->write_buf_len != 0) {
        strcpy(conn->messages[conn->messages_len], conn->write_buf);
        ++conn->messages_len;
        tcp_write(conn->serverfd, conn->write_buf, conn->write_buf_len + 1);
        conn->write_buf[0] = '\0';
        conn->write_buf_len = 0;
    }

    DrawRectangleRec(input_field, TERTIARY_BACKGROUND_COLOR);
    DrawRectangleLines((int)input_field.x, (int)input_field.y, (int)input_field.width, (int)input_field.height, GOLD_YELLOW);
    DrawText(conn->write_buf, (int)input_field.x + 5, (int)input_field.y + 8, FONT_SIZE, FONT_COLOR);
}
