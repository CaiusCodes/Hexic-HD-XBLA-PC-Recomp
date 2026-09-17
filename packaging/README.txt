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
  Game\userdata\             saves, profile and your high scores
  Game\hexic_hd.toml         settings
  Game\logs\                 game logs
  logs\                      Setup logs

Everything stays inside this folder. To move or back up the game, copy the
whole folder. Running Setup again updates the game files and keeps your saves
(userdata) and your settings (hexic_hd.toml). Saves from an earlier portable
build of this port are carried over when this release is extracted over it.

PC SETTINGS
  The main menu's Achievements entry is now PC Settings:
    Player Name          the name shown on High Scores and the new-high-score
                         screen (up to 15 characters; leave it empty to use
                         your Windows user name)
    Display Mode         Windowed or Fullscreen
    Resolution           1280 x 720 up to 3840 x 2160
    VSync, Show FPS
    Keyboard Controls    change the keys (see CONTROLS)
  Changes apply immediately. Xbox Dashboard is now Quit Hexic.

HIGH SCORES
  Leaderboards is now High Scores, and it works offline. Whenever a Marathon,
  Timed or Survival game beats your best for that mode, the game records it -
  the score, the difficulty, the gem counts and your player name - and High
  Scores lists it on that mode's tab. Scores are kept in
  Game\userdata\leaderboards. Changing your player name does not rename scores
  already recorded.

CONTROLS
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

  To change them, open PC Settings > Keyboard Controls. Every controller
  input is listed with its keys:
    Enter / A          change the key (then press the new key; Esc cancels)
    Tab / Y            add a second key
    Backspace / X      reset that input to its default
  Reset All to Defaults restores every key. Giving an input a key that
  another input uses swaps them, so nothing is left without a key. Mouse
  buttons can be bound too.

  The PC Settings panels use the arrow keys, Enter and Esc, or the D-pad, A
  and B.

REQUIREMENTS
  Windows 10 or 11 (64-bit) and a DirectX 12 graphics card. No separate
  runtime installation is needed.

KNOWN LIMITATIONS
  - Xbox LIVE features (online leaderboards, the achievements viewer) are not
    available; High Scores shows this PC's scores instead (see above).
  - The player name can only be typed on a keyboard.

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
