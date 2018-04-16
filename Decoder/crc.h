#ifndef OOT_RANDOMIZER_CRC_H
#define OOT_RANDOMIZER_CRC_H
#ifdef __cplusplus
extern "C" {
#endif

/// Initialize the CRC subsystem.  Not thread-safe!
/// Must be called before any other CRC function.
/// Simplest: call it at the beginning of main().
void OoT_Randomizer_crc_init(void);

#ifdef __cplusplus
}
#endif
#endif // OOT_RANDOMIZER_CRC_H
