This file provides functionality for the MuTC backend of `sac2c`.

FIXME: please note that this module hasn't been properly tested!

  * Check existence of SL compiler 
  * Check that macros are being passed correctly
    Is there a `SAC_BACKEND_MUTC` at all in `sac2c` nowadays?
  * Mysterious `slinclude` directory that contained a single line
    which was a comment and was not included in any of the files under
    this repo has been dropped.  No idea what was the idea behind
    `slinclude`.
  * SL functions in `bench.c` and friends, like `sl_create`, `sl_def`, etc
    --- are they correct; do they work?
