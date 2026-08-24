# Build + artifact flow — Isle Sound Enhancer

Boss rule: **nothing compiles on the Pi** (laggy). All builds run on a
dev machine or the boss's client PC. Artifacts are stored centrally
(GitHub Releases on this repo, or a designated storage path) and shipped
together as a BIG RELEASE bundle. The Pi only ever receives already-built
artifacts + webui file syncs.

## Dev machine / client PC

- Windows x64, Visual Studio 2022 (MSVC) + CMake 3.20+.
- NSIS (for the setup exe) — `install/installer.nsi`.

```
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
makensis install/installer.nsi     # -> IsleSoundEnhancer-Setup.exe
```

## Artifacts produced

- `IsleSoundEnhancer.exe` (the tray app)
- `ise_apo.dll` (APO COM effect; registered on the render endpoint)
- `IsleSoundEnhancer-Setup.exe` (NSIS installer)

Publish these to GitHub Releases (this repo) — the release bundle gate
accumulates and ships them with the other pieces.

## Never

- Compile on the Pi.
- Drop files into the game directory (APO runs in audiodg via COM
  registration; loopback fallback needs no game-dir files either).
- Touch the webui or the Pi as part of install.
