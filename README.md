# sysrq-firefox

A Sysrq for killing Firefox (Don't Ask...)

## Installation

Execute the following commands:

```bash
./autogen.sh
./configure
make
insmod ./src/sysrq-firefox.ko
```

## Usage

Most of the documentation (In fact, the hotkey, but this is a cookiecutter template, i won't rewrite everything) is available in the manual page `sysrq-firefox(4)`.

TLDR: Alt-PrintScreen-x

Special Thanks to:
- https://github.com/nderjung/boilerplate.ko
- Many stackoverflow posts (I can't find them all)
- **The Firefox Team : I love you guys, don't worry, it's not personal <3**

## DISCLAIMER:

**WORKS ON MY MACHINE**
