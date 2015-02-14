#include <stdio.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include "common.h"

#define __USE_GNU
#include <dlfcn.h>

typedef Window (*XCreateWindowFunction)(
        Display*,
        Window,
        int,
        int,
        unsigned int,
        unsigned int,
        unsigned int,
        int,
        unsigned int,
        Visual*,
        unsigned long,
        XSetWindowAttributes*);

typedef int (*XDestroyWindowFunction)(
        Display*,
        Window);

Window XCreateWindow(
        Display *display,
        Window parent,
        int x,
        int y,
        unsigned int width,
        unsigned int height,
        unsigned int border_width,
        int depth,
        unsigned int _class,
        Visual *visual,
        unsigned long valuemask,
        XSetWindowAttributes *attributes)
{
    Window result;
    XCreateWindowFunction hostage = dlsym(RTLD_NEXT, "XCreateWindow");


    result = hostage(display, parent, x, y, width, height, border_width, depth, _class, visual, valuemask, attributes);

    FILE* log = fopen(TEMPFILE, "a");
    fprintf(log, "%i created %lu\n", getpid(), result);
    fclose(log);

    printf("Process %i made window %lu\n", getpid(), result);

    return result;
}

int XDestroyWindow(Display *display, Window window)
{
    XDestroyWindowFunction hostage = dlsym(RTLD_NEXT, "XDestroyWindow");

    FILE* log = fopen(TEMPFILE, "a");
    fprintf(log, "%i destroyed %lu\n", getpid(), window);
    fclose(log);

    printf("Process %i destroyed window %lu\n", getpid(), window);

    return hostage(display, window);
}
