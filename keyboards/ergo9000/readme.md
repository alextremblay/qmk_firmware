# ergo9000

![ergo9000](imgur.com image replace me!)

The Ergo9000 is a full-sized 105-key ortholinear split ergonomic keyboard with an RP2040 microcontroller, an OLED display, a fully custom set of 3d-printable keys, and a few novel software features

It's made out of a pair of Elite-Pi microcontrollers, a pair of BFO-9000 PCBs with case plates, and an SSD1306 128x64 0.96in OLED display

* Keyboard Maintainer: [Alex Tremblay](https://github.com/alextremblay)
* Hardware Supported: *BFO-9000 PCB, Elite-Pi microcontroller, SSD1306 OLED*
* Hardware Availability: *[BFO-9000](https://keeb.io/collections/bfo-9000), [Elite-Pi](https://keeb.io/products/elite-pi-usb-c-pro-micro-replacement-rp2040), [OLED Display](https://www.amazon.ca/dp/B07YNP2L95)*

Make example for this keyboard (after setting up your build environment):

    make ergo9000:default

Flashing example for this keyboard:

    make ergo9000:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
