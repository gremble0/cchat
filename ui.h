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
    Color accent;
    Color font_color;
} CchatUiConf;

void DrawWindow(connection *p, CchatUiConf *conf); /* Main entrypoint to drawing ui elements in the window */
void DrawChatBox(CchatUiConf *conf, char *text, Rectangle boundaries, bool should_use_bg2); /* Draws a box with text for a message */
void DrawTextInBounds(CchatUiConf *conf, char *text, Rectangle boundaries); /* Draw text with line wrapping on characters. TODO: line wrapping on words*/
void DrawInputField(CchatUiConf *conf, connection *p); /* Draws input field and handles sending messages through the connection */
