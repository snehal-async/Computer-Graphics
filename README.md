# Raylib Computer Graphics Lab

Seven standalone C programs turn classic computer-graphics exercises into
interactive Windows demos. Each scene is drawn in real time with [raylib](https://www.raylib.com/)
and can be built independently with MinGW-w64.

## The Programs

| Program | Source | What to explore | Controls |
| --- | --- | --- | --- |
| Analog clock | `01_analog_clock.c` | Clock-face geometry and moving hands | `ESC` or close window |
| Helicopter game | `02_helicopter_game.c` | Input, collision, obstacles, and score | `UP` / `DOWN`; `R` to restart |
| Sinking ship | `03_sinking_ship.c` | Keyboard movement and day/night scenes | `LEFT` / `RIGHT`; `SPACE` |
| Train arrival and departure | `04_train_arrival_departure.c` | State-driven movement | `A` arrive; `S` stop; `D` depart |
| Scientific calculator | `05_scientific_calculator.c` | Mouse input and mathematical operations | Click the buttons |
| Tower of Hanoi | `06_tower_of_hanoi.c` | Recursive puzzle solution, animated | Automatic |
| Bouncing ball | `07_bouncing_ball.c` | Frame-time motion and wall reflections | Automatic |

All windows close with `ESC` or the window close button.

## Windows Setup

This project uses MSYS2's UCRT64 MinGW-w64 toolchain. Install [MSYS2](https://www.msys2.org/),
then open the MSYS2 UCRT64 terminal and install GCC and raylib:

```sh
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-raylib
```

The Microsoft C/C++ extension for VS Code is recommended for IntelliSense and
debugging. In PowerShell, add the UCRT64 tools to the current terminal session
and confirm GCC is available:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
```

## Build Every Program

Run this from the project folder in PowerShell. It places the executables in
`build\` and stops if any compilation fails.

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
$gcc = "C:\msys64\ucrt64\bin\gcc.exe"
$include = "C:\msys64\ucrt64\include"
$lib = "C:\msys64\ucrt64\lib"
New-Item -ItemType Directory -Path build -Force | Out-Null

Get-ChildItem -File -Filter "*.c" | Sort-Object Name | ForEach-Object {
	$output = Join-Path "build" ($_.BaseName + ".exe")
	& $gcc $_.FullName -o $output "-I$include" "-L$lib" `
		-lraylib -lopengl32 -lgdi32 -lwinmm -lm
	if ($LASTEXITCODE -ne 0) {
		throw "Build failed: $($_.Name)"
	}
}
```

## Run

Launch one program:

```powershell
.\build\01_analog_clock.exe
```

Launch every built demo in its own window:

```powershell
Get-ChildItem .\build\*.exe | ForEach-Object {
	Start-Process -FilePath $_.FullName
}
```

Each source file has its own `main` function, so compile them as separate
executables rather than linking them together.
