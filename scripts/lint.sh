#!/usr/bin/env bash
set -euo pipefail

# Use the repository's .clang-format and format files in-place.
# Handle filenames with spaces by using -print0 / xargs -0.

if ! command -v clang-format >/dev/null 2>&1; then
	echo "clang-format not found. Please install clang-format." >&2
	exit 1
fi

find . -type f \( -name '*.cpp' -o -name '*.hpp' \) -print0 \
	| xargs -0 clang-format -i -style=file