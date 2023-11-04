#include <raylib.h>

#define WINDOW_WIDTH   400
#define WINDOW_HEIGHT  700
#define CHATBOX_HEIGHT 50
#define FONT_SIZE      32

#define ALTERNATE_BACKGROUND_COLOR GetColor(0x191919ff)
#define BACKGROUND_COLOR           GetColor(0x151515ff)
#define FONT_COLOR                 GetColor(0xccccccff)

void DrawWindow();     /* Main entrypoint to drawing ui elements in the window */
void DrawNewMessage(); /* Draws a new message onto the screen */
