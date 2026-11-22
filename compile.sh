#!/usr/bin/env bash
# compile.sh - C++20 build helper
#   ./compile.sh                     -> main.cpp + compile.cpp (or all *.cpp)
#   ./compile.sh a.cpp b.cpp         -> build the files you list
#   ./compile.sh -o name a.cpp       -> custom output name
#   ./compile.sh -w ...              -> Windows build with MinGW-w64
#   ./compile.sh -r / --no-raylib    -> force / skip raylib linking (auto by default)
set -e

MODE=mac
OUT=""
RAYLIB=auto
SRCS=()

while (($#)); do
  case "$1" in
    -w|--windows)  MODE=win; shift ;;
    -m|--mac)      MODE=mac; shift ;;
    -r)            RAYLIB=1; shift ;;
    --no-raylib)   RAYLIB=0; shift ;;
    -o)            OUT="${2:?missing output name}"; shift 2 ;;
    -h|--help)     sed -n '2,7p' "$0"; exit 0 ;;
    -*)            echo "Unknown option: $1" >&2; exit 1 ;;
    *.cpp|*.cc|*.cxx) SRCS+=("$1"); shift ;;
    *) shift ;;
  esac
done

if ((${#SRCS[@]} == 0)); then
  if [[ -f compile.cpp ]]; then
    if [[ -f main.cpp ]]; then SRCS+=(main.cpp); fi
    SRCS+=(compile.cpp)
  else
    for d in . src; do
      for f in "$d"/*.cpp; do
        if [[ -e "$f" ]]; then SRCS+=("$f"); fi
      done
    done
  fi
fi
if ((${#SRCS[@]} == 0)); then
  echo "No .cpp sources found" >&2
  exit 1
fi

if [[ "$RAYLIB" == auto ]]; then
  RAYLIB=0
  if grep -l 'raylib\.h' "${SRCS[@]}" >/dev/null 2>&1; then RAYLIB=1; fi
fi

INCLUDES=(-std=c++20 -Wall -Wextra -I. -I"$HOME/.local/include")
LIBS=()

if [[ "$MODE" == win ]]; then
  CXX=/opt/local/bin/x86_64-w64-mingw32-g++
  OUT="${OUT:-game.exe}"
  if ((RAYLIB)); then LIBS=(-L"$HOME/.local/lib" -lraylib -lopengl32 -lgdi32 -lwinmm); fi
else
  CXX=/usr/bin/clang++
  OUT="${OUT:-game}"
  if ((RAYLIB)); then LIBS=(-L"$HOME/.local/lib" -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo); fi
fi

echo "==> $CXX -std=c++20 ${SRCS[*]} -o $OUT"
"$CXX" "${INCLUDES[@]}" "${SRCS[@]}" -o "$OUT" "${LIBS[@]}"
echo "==> built $OUT"
