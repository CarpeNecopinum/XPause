# XPause
Similar to XKill, allows to send SIGSTOP and SIGCONT to windows to effectively pause/unpause them. Works with local clients only.

# Building XPause
1. Clone the repo
2. $ cmake .
3. $ make

# Using XPause
To use XPause, the client you want to control has to be started with LD_PRELOAD pointing to libxintercept.so (for example with "export LD_PRELOAD=/path/to/libxintercept.so" in your .bashrc or XSession.

When you start XPause, clicking a window with the right mouse button will _pause_ the process, clicking it with the left mouse button will _unpause_ it again.

