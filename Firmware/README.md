# Firmware

This firmware uses `pio` as its build tool, you can invoke `pio` directly or use `make` for the
included shortcuts.

## Notes

Nest the startup sequence so it only takes a `break` to return out! ie:

 - Push the start button
 - System enters into the HALT loop, witch enters into the STAB loop, witch enters into the SWING loop!
 - SWING loop will swingup the pendulum and `break` into STAB
 - STAB will try to balance until it tilts out of range, and then `break`s into HALT
 - Halt brings the system back to its normal config.
