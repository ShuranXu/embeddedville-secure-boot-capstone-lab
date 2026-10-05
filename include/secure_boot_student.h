#ifndef EMBEDDEDVILLE_SECURE_BOOT_STUDENT_H
#define EMBEDDEDVILLE_SECURE_BOOT_STUDENT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define SECURE_BOOT_P256_PUBLIC_KEY_BYTES 65u
#define SECURE_BOOT_P256_SIGNATURE_BYTES 64u

typedef enum {
    SECURE_BOOT_VERIFY_OK = 0,
    SECURE_BOOT_VERIFY_BAD_ARGUMENT,
    SECURE_BOOT_VERIFY_SIZE_MISMATCH,
    SECURE_BOOT_VERIFY_DIGEST_MISMATCH,
    SECURE_BOOT_VERIFY_SIGNATURE_INVALID,
    SECURE_BOOT_VERIFY_ROLLBACK,
    SECURE_BOOT_VERIFY_CRYPTO_ERROR
} secure_boot_verify_status_t;

typedef struct {
    uint32_t image_version;
    uint32_t image_size;
    uint8_t image_sha256[32];
    uint8_t signature_rs[SECURE_BOOT_P256_SIGNATURE_BYTES];
} secure_boot_manifest_t;

typedef enum {
    SECURE_BOOT_SLOT_NONE = 0,
    SECURE_BOOT_SLOT_A,
    SECURE_BOOT_SLOT_B
} secure_boot_slot_t;

typedef struct {
    secure_boot_slot_t confirmed_slot;
    secure_boot_slot_t trial_slot;
    uint32_t confirmed_version;
    uint32_t trial_version;
    uint32_t rollback_floor;
    uint8_t trial_attempts_remaining;
    bool confirmation_pending;
} secure_boot_state_t;

secure_boot_verify_status_t secure_boot_verify_image(
    const secure_boot_manifest_t *manifest,
    const uint8_t *image,
    size_t image_size,
    const uint8_t public_key_sec1[SECURE_BOOT_P256_PUBLIC_KEY_BYTES],
    uint32_t rollback_floor);

secure_boot_slot_t secure_boot_select_slot(const secure_boot_state_t *state, bool trial_image_verified);
bool secure_boot_confirm_trial(secure_boot_state_t *state, uint32_t running_version);
bool secure_boot_record_failed_trial(secure_boot_state_t *state);

#endif

