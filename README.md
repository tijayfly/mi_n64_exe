> [!NOTE]
> **This is a fork** of [nickallevato/mi_n64_exe](https://github.com/nickallevato/mi_n64_exe) with a native Windows
> build, bug fixes and quality-of-life enhancements: see [Fork notes](#fork-notes). The changes have been submitted
> upstream as [pull requests](https://github.com/nickallevato/mi_n64_exe/pulls?q=is%3Apr+author%3Atijayfly) and are
> awaiting approval.

<div align="center">

# Mission: Impossible — PC Recomp

**The 1998 N64 classic, running natively on PC.**
60 FPS · widescreen at any resolution · keyboard & mouse · analog camera

[Screenshots](#screenshots) · [Download](#download) · [Controls](#controls) · [Settings](#settings) · [Build](#building) · [Roadmap](docs/ROADMAP.md) · [How it works](#how-it-works)

▶ [Watch PC Port Gameplay Highlights](https://youtu.be/8_9ST7XxMoE)

</div>

---

This is a static recompilation of *Mission: Impossible* (N64, USA) made with
[N64Recomp](https://github.com/N64Recomp/N64Recomp). The game's MIPS code is translated to C, compiled for your PC
and run on [N64ModernRuntime](https://github.com/N64Recomp/N64ModernRuntime), with
[RT64](https://github.com/rt64/rt64) for rendering. It is not an emulator: the game runs as a native program.
The app is built like [BanjoRecomp](https://github.com/BanjoRecomp/BanjoRecomp), on
[RecompFrontend](https://github.com/N64Recomp/RecompFrontend).

> **You need your own ROM.** No ROM or game data is in this repository, only screenshots. Use a dump of *Mission Impossible (USA)*,
> sha1 `7546d5df1fc93fed8205a066f1333fd7dd50c1e1`.

## Fork notes

Each branch is an open pull request to the original repo:

| Branch | Changes |
|---|---|
| `windows-build` | Native Windows x64 build, cross-compiled from Linux. Fixes a crash on starting the game with Direct3D 12. Left/right mouse buttons shoot and aim. App icon. Mouse sensitivity defaults to 50%, so mouselook works straight away. Fixes a crash when destroying a sea mine on Gunboat. |
| `cutscene-pillarbox` | Mission cutscenes run at 25 fps, so voice lines no longer overlap (e.g. "Good luck, Jim" playing over the end of the briefing). The title screen's introduction runs at 30 fps. In widescreen, black 4:3 side bars hide unmodelled parts of the sets in cutscenes, on the IMF handheld screens and around the sniper scope. New **Graphics > Cutscene Framing** setting: **Fill** (default) stretches cutscenes to fill the screen while keeping their original framing, and **4:3** keeps the bars. Screen fades and full-screen pictures (e.g. "THE END") cover the whole screen instead of showing the level beside them. |
| `devtools-fixes` | **Debug > Unlock All Levels** unlocks every level. **Debug > Start in Level** options wrap instead of overlapping. |
| `terminal-room-assist` | New **General > Frustration-free Terminal Room** setting (off by default): in the CIA's Terminal Room, the card reader and the computer start as soon as Ethan calls out that he's at the right height, without lining him up to face them. |

`main` (this page) also adds the fork's credits to the end of the game's credits roll. That change isn't part of a pull
request.

### Windows download

Get **MIRecompiled-win64.zip** from the
[windows-test-1 pre-release](https://github.com/tijayfly/mi_n64_exe/releases/tag/windows-test-1). It's built from all
four branches plus `main`. Unzip it, run `MIRecompiled.exe` and pick your ROM. If Windows reports a missing `MSVCP140.dll`, install
the [Visual C++ Redistributable (x64)](https://aka.ms/vs/17/release/vc_redist.x64.exe). Tested on Windows 11 with
Direct3D 12.

### Building for Windows

The Windows build is cross-compiled on Linux with clang-cl. To build it, check out `windows-build`, then merge
`cutscene-pillarbox` and `devtools-fixes` if you want their changes too (if `CMakeLists.txt` conflicts, keep both
sides). Follow [docs/WINDOWS_CROSS.md](https://github.com/tijayfly/mi_n64_exe/blob/windows-build/docs/WINDOWS_CROSS.md),
after step 1 of [Building](#building).

## Features

| | |
|---|---|
| 🎯 **Keyboard & mouse** | WASD to move and the mouse to turn Ethan. Hold right mouse to aim with the mouse, left click to shoot. Works in the sniper scope and the gunboat turret too. |
| 🕹️ **Analog camera** | The right stick turns Ethan and the camera, like a modern third-person game. |
| ⚡ **60 FPS** | The game's logic runs on the video clock, so the game runs at the same speed as on an N64, just smoother. |
| 🖥️ **High resolution & widescreen** | Renders at your window's resolution with MSAA, widescreen expansion and a HUD that stays in place. |
| 🐧 **Native Linux & Windows** | Linux: native Wayland, starts in under a second, keeps running when the window is hidden. Windows *(this fork)*: native x64 build with Direct3D 12 or Vulkan; see [Fork notes](#fork-notes). |
| 🎮 **All 20 levels** | Every level loads and plays at 60 FPS. |

## Screenshots

| | |
|---|---|
| ![Embassy Function: the ballroom](docs/media/embassy_ballroom.jpg) | ![Embassy Function: a guard in the hallway](docs/media/embassy_guard.jpg) |
| ![CIA Rooftop](docs/media/cia_rooftop.jpg) | ![Train Roof](docs/media/train_roof.jpg) |
| ![Ice Hit: Subpen](docs/media/icehit_truck.jpg) | ![Subpen](docs/media/subpen.jpg) |

1080p, widescreen, captured from the recomp.

## Controls

![Default controls for keyboard, mouse and controller](docs/controls.svg)

Rebind anything in the **Controls** tab of the settings menu (**Esc** on the keyboard, **Back** on a controller).

<details>
<summary>Controls as a table</summary>

| Action | Keyboard & mouse | Controller |
|---|---|---|
| Move | W A S D | Left stick |
| Turn Ethan / camera | Mouse | Right stick |
| Aim, first-person view (hold) | Right mouse, E | Right trigger |
| Shoot / punch | Left mouse, Q | Left trigger |
| Action / jump | Space | A |
| Cycle weapons | Left Shift | X |
| Crouch, item inventory | Left Ctrl, ↓ | Right bumper |
| Sidestep while aiming | ← / → | Y / B |
| Zoom while aiming | ↑ | Right stick click |
| Camera mode | V | Left bumper |
| Rotate camera | J / L | D-pad ← / → |
| Pause / IMF menu | Enter | Start |
| Settings | Esc | Back |

</details>

## Settings

- **Graphics > Frame Rate**: 60 FPS (default) or Original (30). Resolution, MSAA and aspect ratio are on the
  same tab.
- **General > Mouse Sensitivity**: 50% by default. Set it to 0 to turn mouse turning off and free the cursor.
- **General > Analog Camera / Analog Camera Speed**: turning with the right stick.
- **General > Developer Tools**: shows a **Debug** tab with **Start in Level** (skip the intro and menus and start in
  any level), **Unlock All Levels**, and **Load Data Overrides** (edited level data from the `overrides` folder next
  to your settings; see [docs/LEVELS.md](docs/LEVELS.md)).

## Download

Get the latest Linux build from [Releases](https://github.com/nickallevato/mi_n64_exe/releases): the **AppImage**
(one file, `chmod +x` and run) or the **.tar.gz**. Built on Ubuntu 22.04, so it runs on most current distros; needs
Vulkan. Pick your ROM in the launcher on first start.

**Windows:** see [Fork notes](#fork-notes) for this fork's Windows download.

## Building

Linux, with clang. The ROM goes in `rom/`, which git ignores.

**Windows:** see [Fork notes](#fork-notes) for building this fork's Windows version.

```sh
git clone --recurse-submodules https://github.com/nickallevato/mi_n64_exe.git && cd mi_n64_exe
mkdir -p rom && cp "<path>/Mission Impossible (USA).z64" rom/
sudo apt-get install cmake ninja-build clang lld libsdl2-dev libgtk-3-dev libfreetype-dev
```

**1. Disassemble and recompile the game.** This uses tools that stay outside the repo (`tools/` is ignored):

```sh
git clone https://github.com/shygoo/n64sym.git tools/n64sym && make -C tools/n64sym
python3 -m venv tools/venv && tools/venv/bin/pip install 'splat64[mips]'

cd split && ln -sf "../rom/Mission Impossible (USA).z64" baserom.z64 \
  && ../tools/venv/bin/python -m splat split missionimpossible.yaml && cd ..

cmake -S lib/N64ModernRuntime/N64Recomp -B build/n64recomp -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build/n64recomp --target N64Recomp RSPRecomp
scripts/recomp.sh        # game code -> RecompiledFuncs/, audio microcode -> rsp/
```

**2. Build and run the app:**

```sh
cmake -S . -B build/app -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
cmake --build build/app
build/app/MIRecompiled                                             # pick the ROM in the launcher, or
MI_ROM="rom/Mission Impossible (USA).z64" build/app/MIRecompiled   # boot straight into the game
```

## Status

All 20 levels load and play, with music. Full playthroughs haven't been verified yet.

See [docs/ROADMAP.md](docs/ROADMAP.md) for what's done and what's next: full playthroughs, Rumble Pak,
packaging, mod support and texture packs.

## How it works

<details>
<summary>ROM layout</summary>

There's no decomp of this game, so the function list comes from a [splat](https://github.com/ethteck/splat)
disassembly instead of an ELF.

| What | ROM | VRAM |
|---|---|---|
| entrypoint | `0x1000` | `0x80000400` |
| `.text` (CPU code, 1697 funcs) | `0x1000`–`0x84A60` | `0x80000400`– |
| rspboot microcode | `0x84A60`–`0x84C90` | |
| data / rodata | `0x84C90`–`0x94440` | |
| bss (`0x27A00`) | — | `0x80093840` |
| assets (no Yay0/Yaz0/MIO0, no plain code found) | `0x94440`–`0xC00000` | |

`game_main` is at `0x8000E090`. Graphics use F3DEX.NoN 1.21 (RT64 HLE); audio is `n_aspMain`, recompiled with
RSPRecomp.

</details>

<details>
<summary>Runtime fixes</summary>

- **Busy-wait loops** (`[[patches.hook]]` in `mi.us.toml`): the game spins on globals that interrupt-driven
  threads update. ultramodern schedules game threads cooperatively, so those loops get a yield hook.
- **libultra functions n64sym missed** are named in `symbols/manual.txt` so the runtime replaces them (AI, SI,
  EEPROM long read, ...). An unreplaced libultra function that waits on hardware hangs or crashes.
- **Wayland**: on a Wayland session the app uses native Wayland. Through XWayland, NVIDIA's Vulkan presentation
  stalls (the game runs at ~0-2 fps).
- **Vsync and hidden windows**: presentation uses vsync (FIFO), so every game frame gets its own display refresh.
  Mailbox presentation dropped and doubled frames whenever a frame landed near a refresh boundary (visible
  microjitter). On NVIDIA + Wayland, a vsync present blocks while the window is hidden, which would freeze the
  game, so RT64 checks (via present wait) that the last frame reached the screen and skips presenting until it does
  (`patches/deps/plume-wait-for-last-present.patch`, `patches/deps/rt64-skip-present-while-hidden.patch`). A hidden
  window keeps running at 60 FPS.
- **Startup**: SDL audio is initialized before the file-dialog library, and the dialog uses the XDG portal
  instead of in-process GTK; either ordering issue or GTK init could stall startup for 25+ s.
- **Quitting**: the game's threads are never joined, so the app keeps game memory mapped
  (`patches/deps/N64ModernRuntime-keep-rdram-on-quit.patch`) and exits without static destructors once saves are
  written. Before this, quitting crashed in 4 of 5 tries.

</details>

<details>
<summary>Levels and assets</summary>

Levels are stored in compressed "Burp" archives. `scripts/levels/level_export.py` exports any level's geometry
to OBJ with textures. See [docs/LEVELS.md](docs/LEVELS.md) for the level table, archive format and geometry format.

</details>

<details>
<summary>Symbols</summary>

- `symbols/libultra.txt`: libultra functions found by `n64sym -s`. n64sym reports jal-discovered addresses with
  a `0x7` prefix for this ROM (bug: base `0x7FFFF400 & 0xF0000000`); these were corrected to `0x8`. Internal
  `*_text_XXXX` labels and false positives were removed.
- `symbols/manual.txt`: hand-identified names; overrides `libultra.txt`.

Correct libultra names matter: N64Recomp skips or replaces functions by name (`src/symbol_lists.cpp`) so that
N64ModernRuntime can provide its own implementations.

</details>

<details>
<summary>Dev tools</summary>

- `scripts/capture.sh` runs the game in a headless sway compositor (real GPU, invisible), takes screenshots with
  grim and injects controller input through `MI_INPUT`.
- `scripts/level_test.sh` unlocks every level, navigates to one and plays it with random input.
- `scripts/stacks.py` prints the recompiled game threads' call stacks (gdb).
- `scripts/find_spins.py` lists busy-wait loops that need yield hooks.
- `scripts/gen_controls_map.py docs/controls.svg` redraws the controls map.
- `scripts/release/build_linux.sh` builds the release (AppImage and .tar.gz) in an Ubuntu 22.04 container (Docker).
- `MI_STATS=1` prints graphics tasks and VIs per second; `MI_WATCH=addr[:n],...` prints game RAM each second.
- `MI_FRAMETIMES=file` logs a timestamp for every VI and every game frame submitted, for checking frame pacing.
- The decomp (readable C for game functions, swapped in and checked in developer builds) has its own guide:
  [docs/DECOMP.md](docs/DECOMP.md).

</details>

## Yes, AI wrote this

**A note from TiJayFLY:** A huge thank you to **nickallevato** for the original Linux port. Mission: Impossible was
under my tree on Christmas morning 1998, and seeing it run natively on PC after all these years is something I never
expected. This fork adds a Windows build and a few fixes and quality-of-life changes on top of that work, also made
with Claude, and all of it has been offered back upstream as pull requests.

### Original repo AI notes

Claude did the reverse engineering, the runtime fixes, the mouse aim and this README. A human aimed it at the game
and played it. It's all in the commit history. No apologies.

Before this, *Mission: Impossible* had no decomp, no recomp and no PC port. For 28 years, nobody did it by hand.
Now it runs at 60 FPS with mouse aim. That beats nothing.

**Thank you** to the people who built the foundation by hand, over years, so a project like this could happen
in days:
- **Mr-Wiseguy**, for [N64Recomp](https://github.com/N64Recomp/N64Recomp),
  [N64ModernRuntime](https://github.com/N64Recomp/N64ModernRuntime) and
  [Zelda64Recomp](https://github.com/Zelda64Recomp/Zelda64Recomp). They proved static recompilation of N64 games
  works and set the bar for what a PC port should feel like.
- **Dario**, for [RT64](https://github.com/rt64/rt64), which is why this looks good at any resolution.
- The [RecompFrontend](https://github.com/N64Recomp/RecompFrontend) and
  [BanjoRecomp](https://github.com/BanjoRecomp/BanjoRecomp) contributors, for the launcher, menus and input layer
  this app is built on.
- **ethteck** and contributors for [splat](https://github.com/ethteck/splat), and **shygoo** for
  [n64sym](https://github.com/shygoo/n64sym).
- Everyone in the N64 decomp scene who mapped out libultra, the microcodes and the hardware by hand. Every
  function name the tools recognized here traces back to your work.

You did the hard, original part. The grunt work of applying it game by game is ours now: naming thousands of
functions, chasing busy-wait loops, wiring up mouse aim. We'll burn our own subscription and inference on it so you
don't have to spend your weekends on it. You're welcome. Fork it, borrow from it, or ignore it.

*Mission: Impossible* is © its respective owners. This project contains no ROM data or game assets; the screenshots
show the game running in this recomp.
