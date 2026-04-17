@echo off
setlocal

REM Clean ESP-IDF build output safely even when Ninja files are missing or stale.
if exist build\build.ninja (
  echo Found build\build.ninja. Running ninja -C build clean...
  ninja -C build clean
  if errorlevel 1 (
    echo ninja clean failed (likely stale toolchain paths). Removing build\ directly...
    rmdir /s /q build
    if errorlevel 1 goto :fail
  )
) else (
  echo No build\build.ninja found. Removing build\ directly...
  rmdir /s /q build
  if errorlevel 1 goto :fail
)

echo Clean complete
goto :eof

:fail
echo Clean failed
exit /b 1
