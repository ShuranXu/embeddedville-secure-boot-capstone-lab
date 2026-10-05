#!/usr/bin/env bash
set -euo pipefail

for command in cmake git python3 openssl gcc; do
  command -v "$command" >/dev/null || { echo "Missing required tool: $command" >&2; exit 1; }
done

python3 - <<'PY'
from pathlib import Path
required = [
    Path("CMakeLists.txt"),
    Path("include/secure_boot_student.h"),
    Path("src/secure_boot_student.c"),
    Path("tests/public_checks.c"),
    Path("fixtures/training-vector.json"),
]
missing = [str(path) for path in required if not path.is_file()]
if missing:
    raise SystemExit("Missing starter files: " + ", ".join(missing))
PY

python3 -c 'import jinja2, jsonschema'

echo "Secure Boot starter secure-boot-capstone-v1.0.0 is ready."
echo "Mbed TLS is pinned to commit 0a8fda272a5a0abef3b47c91bed37185d5a726b1."

