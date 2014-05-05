HMD SDK Opener
==============

Patcher for oculus .dll files that adds support of the RiftUp! upgrade kit.

BUILD HOWTO
-----------
Note: If you are running Windows, you might want to download the binary
file with static linkage instead.
[HMDSDKOpener.exe](https://github.com/FloopCZ/HMDSDKOpener/raw/master/bin/HMD-SDK-Opener-win32-qt-static.exe)

Open the .pro file in the Qt Creator and build the app.
If your prefer building the app manually, run these commands:

    qmake
    make

USAGE HOWTO
---------

1. Start the application
2. Click "Choose File" and find the .dll file of the Oculus library (usually named OculusPlugin.dll)
3. Click "Patch File"

DISCLAIMER
----------

I am not a developer of the RiftUp! project. Use the software at your own risk!
