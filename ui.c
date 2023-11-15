#include <pthread.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui.h"

// Useful function MeasureTextEx()
// TODO: separate drawing and networking components
void DrawWindow(connection *conn) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "cchat");
    SetTargetFPS(20);

    Font cantarell = LoadFontEx("./assets/Cantarell-Regular.ttf", FONT_SIZE, NULL, 0);
    GenTextureMipmaps(&cantarell.texture);
    SetTextureFilter(cantarell.texture, TEXTURE_FILTER_BILINEAR);

    while (!WindowShouldClose()) {
        BeginDrawing();

        DrawBackground();
        // TODO: inputfield drawing on separate thread?
        DrawInputField(conn);

        // TODO: log whats being drawn?
        // TODO: make it draw your username instead of YOU. make struct for sender and check senders ip?
        for (int i = 0; i < conn->messages_len; i++) {
            char outstr[BUFSIZE]; // + MAX_USERNAME_LEN ???
            if (conn->messages[i]->type == SEND) {
                strcpy(outstr, "YOU: ");
            } else {
                strcpy(outstr, conn->messages[i]->sender);
                strcat(outstr, ": ");
            }
            strcat(outstr, conn->messages[i]->text);

            Rectangle boundaries = {
                .x      = 0,
                .y      = CHATBOX_HEIGHT * i,
                .width  = WINDOW_WIDTH,
                .height = CHATBOX_HEIGHT,
            };

            DrawTextInBounds(cantarell, outstr, boundaries, GOLD_YELLOW);
        }

        EndDrawing();
    }
}

void DrawBackground() {
    ClearBackground(BACKGROUND_COLOR);

    for (int i = 0; i < WINDOW_HEIGHT; i += CHATBOX_HEIGHT * 2)
        DrawRectangle(0, i, WINDOW_WIDTH, CHATBOX_HEIGHT, SECONDARY_BACKGROUND_COLOR);
}

// TODO: add tint to params
void DrawTextInBounds(Font font, char *text, Rectangle boundaries, Color tint) {
    Vector2 draw_pos = { boundaries.x, boundaries.y };

    for (size_t i = 0; i < strlen(text); i++) {
        if (draw_pos.x >= boundaries.width) {
            draw_pos.x = boundaries.x;
            draw_pos.y += font.baseSize;
        }
        DrawTextCodepoint(font, text[i], draw_pos, font.baseSize, tint);
        draw_pos.x += GetGlyphInfo(font, text[i]).advanceX;
    }
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
        message *new_message = (message*)malloc(sizeof(message*));
        new_message->type = SEND;
        new_message->sender = NULL; // TODO: get clients username, assigning .sender otherwise unnecessary
        new_message->text = (char*)malloc(BUFSIZE);

        memcpy(new_message->text, conn->write_buf, BUFSIZE);
        insert_message(conn->messages, new_message, conn->messages_len);
        tcp_write(conn->serverfd, conn->write_buf, conn->write_buf_len + 1);

        if (conn->messages_len < MAX_MESSAGES)
            ++conn->messages_len;

        conn->write_buf[0] = '\0';
        conn->write_buf_len = 0;
    }

    DrawRectangleRec(input_field, TERTIARY_BACKGROUND_COLOR);
    DrawRectangleLines((int)input_field.x, (int)input_field.y, (int)input_field.width, (int)input_field.height, GOLD_YELLOW);
    DrawText(conn->write_buf, (int)input_field.x + 5, (int)input_field.y + 8, FONT_SIZE, FONT_COLOR);
}
