<div align="center">
    <h1>🖌 Tintlib 🎨</h1>
    <p>A lightweight C header-only library for styled output</p>
    <img src="https://github.com/unlyx-xyz/tintlib/actions/workflows/ci.yml/badge.svg">
    <img src="https://img.shields.io/badge/version-v1.3.1-blue">
    <img src="https://img.shields.io/github/license/unlyx-xyz/tintlib">
</div>
<div>

## Usage
```c
#define TINT_LIB_IMPLEMENTATION
#include "tintlib.h"

TL_Sequence seq = {0};
seq.da = (TL_SGRDisplayAttributes){.bold = true, .underline = true, .italic = true};
seq.c3bit4bit.foreground = ANSI_C1_CSI_SGR_FG_BLUE;
seq.c3bit4bit.background = ANSI_C1_CSI_SGR_BG_DEFAULT;

TL_printfc3bit4bit(seq, "Hello %s!", "tintlib");
```

## Install
- Install and put the header-file `tintlib.h` in your project, define the `TINT_LIB_IMPLEMENTATION` macro and just start using it.

## Documentation
- `docs/man/man3` -> detailed documentation there

## Notes
This project is still in WIP, it was made for my own usage, but I thought it would be cool if I share it, there are and there will be a lot of things to correct and change. Thank you for your understanding!
