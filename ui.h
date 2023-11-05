#include <raylib.h>

#include "connection.h"

#define WINDOW_WIDTH   400
#define WINDOW_HEIGHT  700
#define CHATBOX_HEIGHT 50
#define FONT_SIZE      32

#define BACKGROUND_COLOR           GetColor(0x151515ff)
#define SECONDARY_BACKGROUND_COLOR GetColor(0x191919ff)
#define TERTIARY_BACKGROUND_COLOR  GetColor(0x1c1c1cff)
#define FONT_COLOR                 GetColor(0xccccccff)
#define GOLD_YELLOW                GetColor(0xe1b655ff)

void DrawWindow(tcp_io_params *p); /* Main entrypoint to drawing ui elements in the window */
void DrawNewMessage(); /* Draws a new message onto the screen NOTE: assumes BeginDraw() has been called */
void DrawBackground(); /* NOTE: assumes BeginDraw() has been called */
void DrawInputField(tcp_io_params *p); /* NOTE: assumes BeginDraw() has been called */
