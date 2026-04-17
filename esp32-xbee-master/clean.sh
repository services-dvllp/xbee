#!/usr/bin/env bash
set -euo pipefail

# Clean ESP-IDF build output safely even when Ninja files are missing or stale.
if [[ -f build/build.ninja ]]; then
  echo "Found build/build.ninja. Running ninja -C build clean..."
  if ! ninja -C build clean; then
    echo "ninja clean failed (likely stale toolchain paths). Removing build/ directly..."
    rm -rf build
  fi
else
  echo "No build/build.ninja found. Removing build/ directly..."
  rm -rf build
fi

echo "Clean complete"
