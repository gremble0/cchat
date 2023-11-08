#include "connection.h"

// TODO: split into two files, one draw related and one for util
#define WINDOW_WIDTH   475
#define WINDOW_HEIGHT  850
#define CHATBOX_HEIGHT 50
#define FONT_SIZE      18

#define MAX_MESSAGES (WINDOW_HEIGHT / CHATBOX_HEIGHT - 1)

#define BACKGROUND_COLOR           GetColor(0x151515ff)
#define SECONDARY_BACKGROUND_COLOR GetColor(0x191919ff)
#define TERTIARY_BACKGROUND_COLOR  GetColor(0x1c1c1cff)
#define FONT_COLOR                 GetColor(0xccccccff)
#define GOLD_YELLOW                GetColor(0xe1b655ff)

void DrawWindow(connection *p);     /* Main entrypoint to drawing ui elements in the window */
void DrawInputField(connection *p); /* NOTE: assumes BeginDraw() has been called */
void DrawBackground();              /* NOTE: assumes BeginDraw() has been called */
