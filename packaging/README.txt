HEXIC HD PC - SETUP
Version @VERSION@

A native Windows port of the Xbox 360 (Xbox LIVE Arcade) release of Hexic HD,
built with the ReXGlue static recompiler. This download contains no original
game program, artwork, music or other game data. You supply your own legally
obtained package; Setup installs from it.

INSTALLING
  1. Extract this entire folder to a writable place where you want to keep
     the game (not Program Files, and not inside the ZIP).
  2. Open "Install Hexic HD.exe" - the only program in this download.
  3. Click "Choose file..." and select your Xbox 360 Hexic HD package
     (Xbox LIVE Arcade, title ID 584107D1). You can also drag the file onto
     the Setup window.
  4. Click "Install game", pick any extras you want, then "Play now".

Setup installs the game into a Game folder beside it and adds a
"Hexic HD.exe" play button next to Setup. Later, just open:
  Hexic HD.exe

Your package is opened read-only and never changed. Only the audited package
is accepted: Setup checks that the game program inside it is the exact build
this port was recompiled from, and rejects anything else (a title update, a
damaged file, another game) without touching an existing installation.

Windows SmartScreen may say "Windows protected your PC" the first time,
because Setup is not signed with a paid certificate. Choose "More info", then
"Run anyway".

WHERE THINGS LIVE
  Game\                      the installed game
  Game\userdata\             saves, profile and your leaderboard scores
  Game\hexic_hd.toml         settings
  Game\logs\                 game logs
  logs\                      Setup logs

Everything stays inside this folder. To move or back up the game, copy the
whole folder. Running Setup again updates the game files and keeps your saves
(userdata) and your settings (hexic_hd.toml). Saves from an earlier portable
build of this port are carried over when this release is extracted over it.

PC SETTINGS AND LEADERBOARDS
  The main menu's Achievements entry is now PC Settings: Windowed/Fullscreen,
  Resolution (up to 3840 x 2160), Vsync and Show FPS. Changes apply
  immediately. Xbox Dashboard is now Quit Hexic.

  Leaderboards works offline with your own scores. Whenever a Marathon, Timed
  or Survival game beats your best for that mode, the game records it - the
  score, the difficulty and the gem counts - and its own Leaderboards screen
  lists it on that mode's tab. Sort Mode (X) switches between Friends (your
  best score), My Score and Overall. Scores are kept in
  Game\userdata\leaderboards.

CONTROLS
  An Xbox controller works out of the box. To play on the keyboard, tick
  "Keyboard controls" in Setup's extras (or set mnk_mode = true in
  Game\hexic_hd.toml). The keys stand in for controller buttons:
    D-pad                 Arrow keys
    Left stick            W A S D
    A / B / X / Y         Space / Shift / R / E
    Shoulder buttons      Q / F
    Triggers              Right / left mouse button
    Start (pause)         Esc
    Back                  Tab
  In the PC Settings panel use the arrow keys, Enter and Esc.
  To change a key, edit the keybind_ lines in Game\hexic_hd.toml while the
  game is closed.

REQUIREMENTS
  Windows 10 or 11 (64-bit) and a DirectX 12 graphics card. No separate
  runtime installation is needed.

KNOWN LIMITATIONS
  - Xbox LIVE features (online leaderboards, the achievements viewer) are not
    available; Leaderboards shows this PC's scores instead (see above).

TROUBLESHOOTING
  - "Hexic HD.exe" says the game is not installed: run Setup first.
  - Setup rejects the package: choose the Hexic HD game package itself, not a
    title update, save or theme. The reason is in the newest file in the logs
    folder.
  - When reporting a problem, include the newest file from Game\logs (or from
    logs for Setup problems).

LEGAL
Hexic HD, Xbox, Xbox 360 and related names and marks belong to their
respective owners. This project is not affiliated with or endorsed by them.
License notices for the open-source components are in the licenses folder.

The Game folder contains data from your own package. Do not share it; share
only the original download.
