# Teclado programador

He organizado las teclas que mas uso como programador de aplicaciones. Cualquier sugerencia es bienvenida

##  Capa 1

![Capa basica](https://github.com/JairoGC/qmk_firmware/blob/desarrollo/keyboards/crkbd/keymaps/jailux/assets/c11.png)

##  Capa 2

![Funciones y caracteres mas usados](https://github.com/JairoGC/qmk_firmware/blob/desarrollo/keyboards/crkbd/keymaps/jailux/assets/c22.png)

##  Capa 3

![Capa numerica y control de audio](https://github.com/JairoGC/qmk_firmware/blob/desarrollo/keyboards/crkbd/keymaps/jailux/assets/c33.png)

##  Capa 4

![Capa extra](https://github.com/JairoGC/qmk_firmware/blob/desarrollo/keyboards/crkbd/keymaps/jailux/assets/c44.png)

# Instalacion

## Configurar qmk

- qmk config user.keyboard=crkbd
- qmk config user.keymap=jailux

# Compilar 

- qmk compile

# Flashing

- sudo dfu-programmer atmega32u4 erase --force
- sudo dfu-programmer atmega32u4 flash crkbd_rev1_legacy_jailux.hex
- sudo dfu-programmer atmega32u4 reset
