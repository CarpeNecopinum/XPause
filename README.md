# XPause
Similar to XKill, allows to send SIGSTOP and SIGCONT to windows to effectively pause/unpause them. Works with local clients only.

# Building/Installing XPause
1. Clone the repo
2. $ cmake .
3. $ make
4. $ sudo make install # this installs libxintercept to /usr/local/lib and xpause to /usr/local/bin

# Using XPause
To use XPause, the client you want to control has to be started with LD_PRELOAD pointing to libxintercept.so (for example with "export LD_PRELOAD=/usr/local/lib/libxintercept.so" in your .bashrc or .profile.

When you start XPause, clicking a window with the right mouse button will _pause_ the process, clicking it with the left mouse button will _unpause_ it again.

XPause may fail to grab the Cursor (when starting it with i3, for example) if that happens, try "$ xpause --sleep" as a workaround.
