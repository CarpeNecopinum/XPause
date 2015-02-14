#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include <signal.h>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/cursorfont.h>

Window findVictim(unsigned int* button)
{
    Display* display = XOpenDisplay(0);
    if (!display)
    {
        fprintf(stderr, "Could not open display %s\n", XDisplayName(0));
        exit(1);
    }

    Window root = RootWindow (display, XDefaultScreen(display));
    Cursor cursor = XCreateFontCursor (display, XC_bogosity);

    XSync(display, 1);
    if (XGrabPointer(display, root, False, ButtonPressMask, GrabModeSync, GrabModeAsync, None, cursor, CurrentTime) != GrabSuccess)
    {
        fprintf(stderr, "Cursor-grabbing failed!\n");
        exit(1);
    }

    Window victim = None;
    while (victim == None)
    {
        XEvent event;
        XAllowEvents (display, SyncPointer, CurrentTime);
        XWindowEvent (display, root, ButtonPressMask, &event);

        if (event.type == ButtonPress)
        {
            victim = event.xbutton.subwindow;
            *button = event.xbutton.button;
        }
    }
    return victim;
}


void sendSignal(Window victim, int signal)
{
    FILE* file = fopen(TEMPFILE, "r");
    while (!feof(file))
    {
        pid_t process;
        Window window;
        int fields = fscanf(file, "%i created %lu\n", &process, &window);
        if (fields == 2 && window )
        {
            kill(process, signal);
        }
    }

}

char* g_ProgName;

int main(int argc, char** argv)
{
    int i;
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--sleep") == 0) usleep(250000); // 1/4 seconds
    }

    unsigned int button;
    Window xid = findVictim(&button);

    printf("I think you clicked window %d with button %u\n", xid, button);

    switch (button)
    {
        case 1: // Left Mouse Button => continue
            sendSignal(xid, SIGCONT);
            break;
        case 3: // Right Mouse Button => stop
            sendSignal(xid, SIGSTOP);
            break;
    }

    return 0;
}
