#include "secure_boot_student.h"

#include <psa/crypto.h>
#include <string.h>

secure_boot_verify_status_t secure_boot_verify_image(
    const secure_boot_manifest_t *manifest,
    const uint8_t *image,
    size_t image_size,
    const uint8_t public_key_sec1[SECURE_BOOT_P256_PUBLIC_KEY_BYTES],
    uint32_t rollback_floor)
{
    if (!manifest || !image || !public_key_sec1) {
        return SECURE_BOOT_VERIFY_BAD_ARGUMENT;
    }
    if (manifest->image_size != image_size) {
        return SECURE_BOOT_VERIFY_SIZE_MISMATCH;
    }
    if (manifest->image_version < rollback_floor) {
        return SECURE_BOOT_VERIFY_ROLLBACK;
    }

    /* TODO(course):
     * 1. Initialize PSA Crypto.
     * 2. Hash exactly image_size bytes with SHA-256.
     * 3. Compare the computed digest with manifest->image_sha256 in constant time.
     * 4. Serialize EVSB1 || version_be32 || size_be32 || image_sha256 and hash it.
     * 5. Import only the uncompressed secp256r1 public key.
     * 6. Verify the raw r||s ECDSA signature over the release-statement digest.
     * 7. Destroy the transient PSA key handle on every path.
     */
    (void)image;
    return SECURE_BOOT_VERIFY_CRYPTO_ERROR;
}

secure_boot_slot_t secure_boot_select_slot(const secure_boot_state_t *state, bool trial_image_verified)
{
    if (!state) {
        return SECURE_BOOT_SLOT_NONE;
    }
    /* TODO(course): prefer a verified, pending trial only while attempts remain;
     * otherwise return the confirmed slot. Never select an unverified trial. */
    (void)trial_image_verified;
    return SECURE_BOOT_SLOT_NONE;
}

bool secure_boot_confirm_trial(secure_boot_state_t *state, uint32_t running_version)
{
    /* TODO(course): atomically promote the running trial and advance the rollback floor. */
    (void)state;
    (void)running_version;
    return false;
}

bool secure_boot_record_failed_trial(secure_boot_state_t *state)
{
    /* TODO(course): consume one attempt without corrupting the confirmed fallback. */
    (void)state;
    return false;
}

