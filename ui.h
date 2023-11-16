#include "connection.h"
#include <raylib.h>
#include <stdbool.h>

// TODO: split into two files, one draw related and one for util
#define WINDOW_WIDTH   475
#define WINDOW_HEIGHT  850
#define CHATBOX_HEIGHT 50

#define MAX_MESSAGES (WINDOW_HEIGHT / CHATBOX_HEIGHT - 1)

typedef struct CchatUiConf {
    Font font;
    Color bg1;
    Color bg2;
    Color bg3;
    Color accent_color;
    Color font_color;
} CchatUiConf;

void DrawWindow(CchatUiConf *conf, connection *p); /* Main entrypoint to drawing ui elements in the window */
void DrawChatBox(CchatUiConf *conf, message *msg, Rectangle boundaries, bool should_use_bg2); /* Draws a box with text for a message */
void DrawInputField(CchatUiConf *conf, connection *p); /* Draws input field and handles sending messages through the connection */

/* Raylib extensions */
void DrawTextInBounds(Font font, char *text, Rectangle *boundaries, float fontSize, Color tint);
