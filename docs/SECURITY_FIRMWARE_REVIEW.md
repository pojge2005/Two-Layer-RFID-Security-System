# RFID Security Firmware Review

## Scope

This is a source-level review of `main.c` and the project README. No firmware behavior has been changed by this review.

## Findings to address

1. **PIN input bounds:** The keypad scan loop writes to `pass[i]` while incrementing `i`. Every write must be guarded so the index remains within the four-element PIN buffer, including when more than one key appears pressed during a scan cycle.
2. **Keypad row selection:** The expression `r0=r1==1;` is likely an assignment/comparison typo. Correct row-drive behavior must be checked against the actual keypad wiring before changing it.
3. **Repeated key input:** The scan loop does not clearly wait for key release or provide per-key debounce. A held key may be accepted more than once.
4. **Credential management:** The source contains a hard-coded RFID identifier and compares against a fixed PIN. Treat these as demonstration credentials; do not use real access-control credentials in a public repository.
5. **RFID framing and UART errors:** The code reads a fixed number of UART bytes without validating a complete frame, timeout, or receive overrun/framing errors. Confirm the EM-18 output format and validate the complete frame before authorization.
6. **Hardware configuration:** Pin mappings in the source and README are inconsistent. Reconcile the LCD, keypad, and relay pin assignments against the actual schematic before firmware changes.
7. **Build reproducibility:** The repository needs a verified XC8/MPLAB X build procedure and a check that any committed HEX file is generated from the reviewed source.

## Verification status

- Reviewed the current default-branch `main.c` and `README.md`.
- No firmware source was changed in this commit.
- No XC8 build, hardware test, or automated regression test was run.
- This review is not a security certification. Do not deploy this prototype as production access-control firmware until the findings are addressed and hardware behavior is tested.

## Recommended implementation order

1. Confirm the schematic and actual keypad pin mapping.
2. Fix PIN buffer bounds and row selection.
3. Add key-release handling and debounce.
4. Validate RFID UART framing and error handling.
5. Add host-side tests for input handling where practical, then build with the intended XC8 toolchain and test on hardware.
