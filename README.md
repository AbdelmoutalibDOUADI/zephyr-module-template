# zephyr-module-template

My first [Zephyr RTOS](https://www.zephyrproject.org/) project: a minimal **out-of-tree Zephyr module** that bundles a custom library, its Kconfig options and a sample application, all managed with `west`.

It is meant as a clean starting point for future Zephyr projects and as a hands-on reference for how the pieces fit together.

## What it demonstrates

- **Zephyr module structure** declared in `zephyr/module.yml` (CMake, Kconfig, board and DTS roots)
- **A custom library** (`mylib`) compiled only when enabled with `CONFIG_MYLIB`
- **Custom Kconfig options**, visible in menuconfig under *Modules → Custom Libraries*
- **Application versioning** with a `VERSION` file and `<zephyr/app_version.h>`
- **A west manifest** (`west.yml`) that pulls Zephyr and only the HALs needed (`cmsis_6`, `hal_stm32`)

## Repository layout

```
.
├── west.yml                 # west manifest: Zephyr + required HAL modules
├── zephyr/module.yml        # declares this repo as a Zephyr module
├── CMakeLists.txt           # module CMake entry point
├── Kconfig                  # module Kconfig entry point
├── include/lib/mylib.h      # public header of the library
├── lib/
│   ├── CMakeLists.txt
│   ├── Kconfig              # "Custom Libraries" menu
│   └── mylib/
│       ├── CMakeLists.txt
│       ├── Kconfig          # CONFIG_MYLIB, CONFIG_MYLIB_ANSWER
│       └── mylib.c
└── my_app/                  # sample application
    ├── CMakeLists.txt
    ├── prj.conf             # enables CONFIG_MYLIB
    ├── VERSION              # application version (1.2.3+4)
    └── src/main.c
```

## The library: `mylib`

`get_lib(char *output, int input)` writes `input` as a string into `output`, except when `input` equals `CONFIG_MYLIB_ANSWER` (default **42**, a nod to *The Hitchhiker's Guide to the Galaxy*), where it writes a special message instead.

| Kconfig option        | Type | Default | Description                           |
|-----------------------|------|---------|---------------------------------------|
| `CONFIG_MYLIB`        | bool | n       | Builds and links the library          |
| `CONFIG_MYLIB_ANSWER` | int  | 42      | Value that triggers the special message |

The value can be changed without touching the C code, for example in `my_app/prj.conf`:

```
CONFIG_MYLIB=y
CONFIG_MYLIB_ANSWER=7
```

## The application

`my_app` loops forever, prints its version (`APP_VERSION_STRING`, generated from `my_app/VERSION`) and the output of `get_lib()` for a counter going from 0 to 59, every 250 ms.

## Getting started

### Prerequisites

- Zephyr SDK and host tools installed ([Zephyr Getting Started guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html))
- `west` installed in a Python virtual environment

### Create the workspace

```bash
west init -m https://github.com/AbdelmoutalibDOUADI/zephyr-module-template --mr main my-workspace
cd my-workspace
west update
```

### Build and flash

```bash
west build -b nucleo_l152re zephyr-module-template/my_app -p
west flash
```

### See the output

Open the ST-LINK virtual serial port at 115200 baud:

```bash
minicom -D /dev/ttyACM0 -b 115200
```

Expected output:

```
Bonjour c Abdel  1.2.3
Computing : 0
Bonjour c Abdel  1.2.3
Computing : 1
...
```

## Tested on

| Board          | MCU                    | Zephyr        |
|----------------|------------------------|---------------|
| NUCLEO-L152RE  | STM32L152RE (Cortex-M3) | 4.5.99 (main) |

Other boards should work as long as their HAL is added to `name-allowlist` in `west.yml`.

## Author

**Abdelmoutalib Douadi**, Mechatronics & Embedded Systems engineering student
[Portfolio](https://abdelmoutalib-douadi.netlify.app) · [GitHub](https://github.com/AbdelmoutalibDOUADI)
