HEXIC HD PC
===========
Version @VERSION@

A native Windows port of the Xbox 360 (Xbox LIVE Arcade) release of Hexic HD,
built with the ReXGlue static recompiler. This download contains no original
game program, artwork, music or other game data. You supply your own legally
obtained package; the first time you open the game it imports from it.

IMPORTANT
---------

You need your own copy of Hexic HD XBLA: the Xbox 360 package for

  Hexic HD (Xbox LIVE Arcade)
  Xbox 360 Title ID: 584107D1

The first time you start the game it reads the package you provide, checks
that it is the supported version and imports the game data from it into this
folder. After that the package is not needed any more.

Requirements:
  Windows 10 or 11 (64-bit) and a DirectX 12 capable graphics card.
  Nothing else needs installing: the Microsoft Visual C++ runtime the game
  uses is included.

FIRST-TIME SETUP
----------------

1. Extract the release ZIP to a writable folder (not Program Files, and not
   inside the ZIP). You get one folder, "Hexic HD PC".
   Tip: put your package file beside "Hexic HD.exe", or in a folder called
   "Game Package" next to it, and it is found automatically.
2. Open "Hexic HD.exe". The first time, the setup window opens.
3. If your package was found it is checked and imported straight away.
   Otherwise drag the package file or the folder holding it onto the window,
   or click "Browse package". Setup checks it first and tells you if it is
   the wrong file or an unsupported version; the import starts as soon as it
   is accepted. You can cancel it at any time.
4. Tick any extras you want (both optional, both off unless ticked):
     Start in fullscreen, Create desktop shortcut.
5. Click PLAY once it says HEXIC HD IS READY.

From then on, opening "Hexic HD.exe" starts the game straight away. Setup
only reads your package; it never changes, moves or deletes it, and it is not
needed again. Nothing is installed outside this folder and no administrator
rights are needed. It does not download anything and does not contact
Xbox LIVE.

SETTINGS
-----------

The main menu's Achievements entry is now Settings:
  Player Name          the name shown on High Scores and the new-high-score
                       screen (up to 15 characters; leave it empty to use
                       your Windows user name)
  Display Mode         Windowed or Fullscreen
  Resolution           Window size, 1280 x 720 up to 3840 x 2160
  Render Scale         1x (default), 2x or 3x: renders the picture at 2 or
                       3 times the detail in each direction. Sharper on
                       large windows, but more work for the graphics card
  VSync                The game always runs at 60 fps. On: no tearing.
                       Off: frames reach the screen sooner, may tear
  Show FPS
  Keyboard Controls    change the keys (see CONTROLS)
Changes apply immediately. Xbox Dashboard is now Quit Hexic.

HIGH SCORES
-----------

Leaderboards is now High Scores, and it works offline. Whenever a Marathon,
Timed or Survival game beats your best for that mode, the game records it -
the score, the difficulty, the gem counts and your player name - and High
Scores lists it on that mode's tab. Scores are kept in
resources\userdata\leaderboards. Changing your player name does not rename
scores already recorded.

CONTROLS
--------

Keyboard and an Xbox controller both work, at the same time. Each key stands
in for a controller input. The defaults:
  Move                        Arrow keys (D-pad) or W A S D (left stick)
  Rotate clockwise, select    Space or Enter (A)
  Rotate counter-clockwise    Q (X)
  Rotate with the triggers    Z (left trigger) / X (right trigger)
  Back                        Backspace (B)
  Pause                       Esc (Start)
  Y, bumpers, Back button     E, 1 / 3, Tab
  Right stick                 I J K L, stick clicks C / V

To change them, open Settings > Keyboard Controls. Every controller input
is listed with its keys:
  Enter / A          change the key (then press the new key; Esc cancels)
  Tab / Y            add a second key
  Backspace / X      reset that input to its default
Reset All to Defaults restores every key. Giving an input a key that another
input uses swaps them, so nothing is left without a key. Mouse buttons can be
bound too.

The Settings panels use the arrow keys, Enter and Esc, or the D-pad, A and
B.

PORTABLE DATA
-------------

Everything stays inside the extracted "Hexic HD PC" folder:

  Hexic HD.exe                Open this to play (and to set up the first time)
  README.txt, licenses\       This file and the third-party notices
  resources\
    runtime\                  The game program and its DLLs
      logs\                   Game and setup logs
    assets\                   Game data imported from your package
    userdata\                 Saves, high scores, caches and hexic_hd.toml
                              (display, audio and control settings)

Paths are relative, so the folder can be moved or copied anywhere (a USB
drive works too). To back up your progress, copy resources\userdata.

SETUP AGAIN, UPDATING AND OLDER RELEASES
----------------------------------------

To change your extras or import your package again, start the game with
--setup (for example from a shortcut whose target ends in
"Hexic HD.exe" --setup). Importing again replaces resources\assets only;
saves, high scores and settings in resources\userdata are kept. If a needed
file goes missing, opening Hexic HD.exe shows the setup window again by itself.

To update, extract a new release over this folder (your resources\assets and
resources\userdata are kept), or into a new folder: setup finds the old copy
next to it and imports from it.

Coming from an older release (Install Hexic HD.exe and a Game folder, or the
very first portable builds with the game files beside the program): extract
this release into the old release folder or next to it. Setup finds the old
game data and offers it alongside any package, so you do not need the package
again, and your saves, high scores and settings come with it. The old folder
is never changed or deleted; remove it yourself once you are happy.

KNOWN LIMITATIONS
-----------------

- Xbox LIVE features (online leaderboards, the achievements viewer) are not
  available; High Scores shows this PC's scores instead (see above).
- The player name can only be typed on a keyboard.

TROUBLESHOOTING
---------------

Extract the ZIP first. Do not run Hexic HD.exe from inside the ZIP.

Hexic HD.exe is not digitally signed, so the first time you open it Windows
may show "Windows protected your PC". Choose More info, then Run anyway.

If the game stutters, add the line
  vblank_timing_log = true
to resources\userdata\hexic_hd.toml, play until it happens, then send the
newest log from resources\runtime\logs. Every 10 seconds it records frame
timing and any slow frame with what the game was waiting on. Remove the line
again afterwards.

If setup rejects your package, the reason is shown in the window and in
resources\runtime\logs\setup.log. Choose the Hexic HD game package itself, not
a title update, save or theme. When reporting a problem, include the newest
files from resources\runtime\logs.

LEGAL
-----

Hexic HD, Xbox, Xbox 360 and related names and marks belong to their
respective owners. This project is not affiliated with or endorsed by them.
Third-party notices and license texts are in the licenses folder.

After setup, resources\assets contains data from your own package. Do not
share the folder once you have played from it; share the release ZIP instead.

Hexic HD.exe in the main folder (the launcher and setup) includes a package
reader derived from Velocity and is licensed under the GNU GPL version 3
(licenses\LICENSE-Extract-STFS.txt); its source is in the project repository.
The game in resources\runtime is a separate program and is not covered by the
GPL; its components and their licences are listed in the licenses folder.
