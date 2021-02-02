# Teulu v0.0.3 (2021-02-02)
## Reworked controls and documentation

Controls have been reworked so that double-clicking with left mouse button
dashes, while pressing and holding will make the bumbarrel fly continuously
towards the cursor. The right mouse button still works differently from what
the documentation says: Double-clicking the right mouse button now makes the
bird perch, while single click just changes direction.

Aside from this, the code has been refactored a bit, some minor issues fixed,
screen has been increased to 640x480 from 320x240 (not sure which is better),
and release notes have been included in the build.


--------------
# Teulu v0.0.2 (2021-02-01)
## Fix memory leak

This release only fixes the memory leak (#1) and provides some code clean-up.
Refer to release _v0.0.1_ for further release notes.


--------------
# Teulu v0.0.1 (2021-01-31)
## Initial early alpha releas (caution! memory leak!)

Initial very early development release of _Teulu_. Basic movement works, but
the right mouse button works differently from what the documentation says for
now, prompting immediate perching.

The game appears to have a memory leak that can freeze the computer until the
OS kills it (issue #1). It seems fairly benign, but use q or esc to
pre-emptively quit before this happens.

Note that the build artefact requires _SDL1.2_ to be installed in order to
run. I'll see if I can get it to build with it bundled in the future.

