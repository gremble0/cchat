#include <pthread.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui.h"

// TODO: separate drawing and networking components
void DrawWindow(CchatUiConf *conf, connection *conn) {
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(conf->bg1);
        // TODO: inputfield drawing on separate thread?
        DrawInputField(conf, conn);

        // TODO: log whats being drawn?
        // TODO: make it draw your username instead of YOU. make struct for sender and check senders ip?
        bool should_use_bg2 = true;
        for (int i = 0; i < conn->messages_len; i++) {
            char margin = 1;
            Rectangle boundaries = {
                .x      = 0 + margin,
                .y      = CHATBOX_HEIGHT * i + margin,
                .width  = WINDOW_WIDTH - margin,
                .height = CHATBOX_HEIGHT,
            };

            DrawChatBox(conf, conn->messages[i], boundaries, should_use_bg2);
            should_use_bg2 = !should_use_bg2;
        }

        EndDrawing();
    }
}

void DrawChatBox(CchatUiConf *conf, message *msg, Rectangle boundaries, bool should_use_bg2) {
    DrawRectangle(boundaries.x, boundaries.y, boundaries.width, boundaries.height, should_use_bg2 ? conf->bg2 : conf->bg1);

    DrawTextInBounds(conf->font, msg->sender, &boundaries, conf->font.baseSize, conf->accent_color);
    DrawTextInBounds(conf->font, msg->text, NULL, conf->font.baseSize, conf->font_color);
}

void DrawInputField(CchatUiConf *conf, connection *conn) {
    static Rectangle input_field = {
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
        message *new_message = (message*)malloc(sizeof(message*));
        new_message->type = SEND;
        new_message->sender = "ME: "; // TODO: get clients username, assigning .sender otherwise unnecessary
        new_message->text = (char*)malloc(BUFSIZE);

        memcpy(new_message->text, conn->write_buf, BUFSIZE);
        insert_message(conn->messages, new_message, conn->messages_len);
        tcp_write(conn->serverfd, conn->write_buf, conn->write_buf_len + 1);

        if (conn->messages_len < MAX_MESSAGES)
            ++conn->messages_len;

        conn->write_buf[0] = '\0';
        conn->write_buf_len = 0;
    }

    DrawRectangleRec(input_field, conf->bg3);
    DrawRectangleLines((int)input_field.x, (int)input_field.y, (int)input_field.width, (int)input_field.height, conf->accent_color);
    /* DrawTextInBounds(conf, conn->write_buf, input_field); */
    DrawTextInBounds(conf->font, conn->write_buf, &input_field, conf->font.baseSize, conf->font_color);
}

void DrawTextInBounds(Font font, char *text, Rectangle *boundaries, float fontSize, Color tint) {
    // Keep state of previous values so we can continue drawing from where we left of
    static Vector2 draw_pos = {0};
    static Rectangle prev_boundaries = {0};
    if (boundaries != NULL) {
        draw_pos.x = boundaries->x;
        draw_pos.y = boundaries->y;

        prev_boundaries = *boundaries;
    }

    for (size_t i = 0; i < strlen(text); i++) {
        // Wrap to next line if exceeded width
        if (draw_pos.x >= prev_boundaries.width) {
            draw_pos.x = prev_boundaries.x;
            draw_pos.y += fontSize;
        }
        DrawTextCodepoint(font, text[i], draw_pos, fontSize, tint);
        draw_pos.x += GetGlyphInfo(font, text[i]).advanceX;
    }
}
