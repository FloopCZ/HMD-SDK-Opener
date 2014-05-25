HMD SDK Opener
==============

Patcher for oculus .dll files that adds support of the RiftUp! upgrade kit.

BUILD HOWTO
-----------
Note: If you are running Windows, you might want to download the binary
file with static linkage instead.
[HMD-SDK-Opener.exe](https://github.com/FloopCZ/HMD-SDK-Opener/raw/master/bin/HMD-SDK-Opener-win32-qt-static.exe)

Open the .pro file in the Qt Creator and build the app.
If your prefer building the app manually, run these commands:

    qmake
    make

USAGE HOWTO
-----------
Build or [download](https://github.com/FloopCZ/HMD-SDK-Opener/raw/master/bin/HMD-SDK-Opener-win32-qt-static.exe) the application.

0. (The kit has to be set to identify itself as OVR0002 - see below)
1. Start the application
2. Click "Choose File" and find the .dll file of the Oculus library (usually named OculusPlugin.dll)
3. Click "Patch File". A backup will be created automatically.

CHANGING EDID
-------------
By user rozsnyo on http://www.mtbs3d.com/

The unit will present itself with RZS0002 (default) or OVR0002 (Oculus HD prototype) EDID VID and PID. To switch between these, the following combinations are used:

[1+3+4] PWR + BRDN + CNUP = switch to RZS0002 (magenta)

[1+3+5] PWR + BRDN + CNDN = switch to OVR0002 (cyan)

After transition to different EDID VID/PID, you have to unplug the signal cable from the unit or PC, wait few seconds and replug it.

CONTACT
-------
In case of problems or feature requests, please contact me at riftup SNAIL floop.cz.

DISCLAIMER
----------
I am not a developer of the RiftUp! project. Use the software at your own risk!
