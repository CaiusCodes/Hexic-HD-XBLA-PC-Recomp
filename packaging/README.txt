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
  Windows 10 or 11 (64-bit), a processor from 2015 onwards (the game needs
  AVX2; older processors cannot start it), and a graphics card with
  DirectX 12 or Vulkan.
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
4. Tick any extras you want (all optional, all off unless ticked):
     Start in fullscreen, Create desktop shortcut, and Keep saves and
     settings in another folder ("Choose folder" picks it; see PORTABLE DATA).
   Language (< and >) picks the game's text; Auto follows Windows. It can be
   changed later in Settings > Player.
5. Click PLAY once it says HEXIC HD IS READY.

From then on, opening "Hexic HD.exe" starts the game straight away. Setup
only reads your package; it never changes, moves or deletes it, and it is not
needed again. Nothing is installed outside this folder and no administrator
rights are needed. It does not download anything and does not contact
Xbox LIVE.

SETTINGS
--------

The main menu's Achievements entry is now Settings. Its categories run down
the left: switch with LB / RB, Q / E, or a click. Up / Down picks a setting,
Left / Right changes it (or click a choice), A / Enter opens a page, and
B / Esc or a right click closes. Categories: Display, Graphics, Player,
Controls and Updates.

Display
  Display mode         Windowed or Fullscreen
  Window size          1280 x 720, 1920 x 1080, 2560 x 1440 or 3840 x 2160
  VSync                The game always runs at 60 fps. On: no tearing.
                       Off: frames reach the screen sooner, may tear
  Show FPS             Frame rate in the top corner
Graphics
  Render scale         1x (default), 2x or 3x: renders the picture at 2 or
                       3 times the detail in each direction. Sharper on
                       large windows, but more work for the graphics card
  Anti-aliasing        Off (default), FXAA or Extreme: smooths edges on the
                       finished picture (slightly softens text)
  Upscaling            Off (default) or FSR: AMD FidelityFX Super Resolution
                       1 sharpens the picture when the window is larger than
                       1280 x 720. Very cheap
  Renderer             Auto (default), D3D12 or Vulkan. Auto uses Direct3D
                       12 on NVIDIA cards and Vulkan on AMD and Intel.
                       Applies the next time you start the game. If the
                       chosen one cannot start, the game uses the other one
Player
  Player name          Shown on High Scores and the new-high-score screen
                       (up to 15 characters). The game picks a fun name for
                       you the first time; leave it empty to get another
  Language             The game's text: Auto (your Windows language, the
                       default), English, Deutsch, Espanol, Francais,
                       Italiano, Portugues, Japanese, Korean or Chinese
                       (Traditional). Applies the next time you start the
                       game. The PC screens (Settings, setup) stay in English
Controls
  (the key list)       Change the keys (see CONTROLS)
Updates
  Check for Updates    Shows your version. Press it to ask GitHub whether a
                       newer release of this port exists (see UPDATES)

Changes apply immediately, except Renderer, Language, and VSync when the
renderer is Vulkan (these apply after a restart). Xbox Dashboard is now Quit Hexic, and
the game's own Options screen (sound, piece pattern, credits) is now Game
Options.

UPDATES
-------

Settings > Updates > Check for Updates asks GitHub for this port's latest
release. Nothing is ever checked in the background or at start, only when you
press it, and nothing is sent but that request. If a newer version exists, it
says which and offers Update (from the main menu only; mid-game it asks you to
quit to the main menu first). Update closes the game and opens the Hexic HD
window, which downloads the release ZIP, checks it against the SHA-256 that
GitHub publishes for it, and replaces the program files: Hexic HD.exe,
README.txt, licenses\ and resources\runtime\. Your imported game data
(resources\assets) and your saves, high scores and settings
(resources\userdata) are never touched. If anything goes wrong, every file is
put back as it was and the game is left unchanged. Then the game starts again.
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
  Rotate clockwise, select    E, Space or Enter (A); left click in a game
  Rotate counter-clockwise    Q (X); right click in a game
  Rotate with the triggers    Z (left trigger) / X (right trigger)
  Back                        Backspace (B)
  Pause                       Esc (Start)
  Bumpers, Back button        1 / 3, Tab
  Right stick                 I J K L, stick clicks C / V

To change them, open Settings > Controls. Every controller input is listed
with its keys:
  Click / Enter / A  change the key (then press the new key; Esc or a click
                     cancels)
  + Add / Tab / Y    add another key (up to three)
  Reset / Backspace / X   reset that input to its default
"Reset all" at the end restores every key. Giving an input a key that another
input uses swaps them, so nothing is left without a key. Mouse buttons are not
bound: the mouse plays the game by itself (see above).

The Settings panels use the arrow keys, Enter and Esc, or the D-pad, A and
B, or the mouse.

The game's menus work with the mouse too: point at a button to highlight it,
left click to choose it, right click to go back. On Game Options, click the
arrows to change a setting. In a game, point at the board to move the
cursor; left click rotates the three pieces clockwise, right click
counter-clockwise.

On the title screen any key, or a click in the game window, continues. With
no controller connected when the game starts, the title screen says "Press
any key to continue."

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

Saves elsewhere (optional). In setup ("Hexic HD.exe --setup" reopens it),
tick "Keep saves and settings in another folder" and choose a folder, for
example in Documents or on another drive; it applies when you press Play.
Your current saves, high scores and settings are copied there (files already
in that folder are never overwritten, and the old copy is left as it was),
and resources\userdata-location.txt records the folder. Untick it to go back
to resources\userdata. Updates never change this. If the chosen folder is
missing when you start (a drive not connected), Hexic HD says so instead of
starting with empty saves.

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

If the picture is wrong, black or the game closes on start, try the other
renderer: Settings > Renderer, or the line gpu = "vulkan" (or "d3d12") in
resources\userdata\hexic_hd.toml.

If the game stutters, add the line
  vblank_timing_log = true
to resources\userdata\hexic_hd.toml, play until it happens, then send the
newest log from resources\runtime\logs. Every 10 seconds it records frame
timing and any slow frame with what the game was waiting on. Remove the line
again afterwards.

If setup rejects your package, the reason is shown in the window and in
resources\runtime\logs\setup.log. Choose the Hexic HD game package itself, not
a title update, save or theme. The port is made from one build of the game,
version 2.0.1884.0 (the Xbox Live Arcade release); a package holding any other
build, or a modified copy, is refused. When reporting a problem, include the
newest files from resources\runtime\logs.

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
