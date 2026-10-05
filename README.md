# Secure Boot and Release Capstone — learner starter

This repository is the public, incomplete starter for the EmbeddedVille course. It contains only learner scaffolding, public training vectors, and local checks. Protected tests, reference solutions, and signing private keys are not included.

## Workspace identity

- Course: `firmware-secure-boot-capstone`
- Starter version: `secure-boot-capstone-v1.0.0`
- Authoritative target: QEMU Cortex-M plus host-side cryptographic verification
- Cryptography: SHA-256 and ECDSA-P256 (`secp256r1`) through Mbed TLS 4.1.1 PSA Crypto
- Mbed TLS source: tag `mbedtls-4.1.1`, commit `0a8fda272a5a0abef3b47c91bed37185d5a726b1`

The fixed training fixture includes a public key and signature, never a signing private key. It is deliberately non-production material.

The fixture in `fixtures/training-vector.json` signs the canonical byte sequence `ASCII "EVSB1" || image_version (uint32 big-endian) || image_size (uint32 big-endian) || image_sha256`. SHA-256 hashes that 45-byte release statement, and ECDSA-P256 signs the resulting digest. The fixture-generation private key is not retained or distributed.

## First useful action

```bash
./scripts/readiness.sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j2
ctest --test-dir build --output-on-failure
```

The baseline builds, but the public tests report unfinished verification and boot-state decisions until you complete the `TODO(course)` blocks in `src/secure_boot_student.c`.

Return to the course page for the ordered procedure, expected observations, evidence package, and submission action. Do not place real firmware-signing keys in this repository or Codespaces.

## Persistence and cost boundaries

Saving a file in Codespaces preserves it while the codespace exists; committing and pushing to your own repository is the durable path. Stopping compute normally preserves saved workspace files. Rebuilding can replace container state outside the repository, and deleting or retention expiry can remove unpushed work. Codespaces availability and billing depend on your GitHub account and quota—close the browser to leave the editor, stop the codespace to stop compute, and delete it only after exporting or pushing work you want to keep.

