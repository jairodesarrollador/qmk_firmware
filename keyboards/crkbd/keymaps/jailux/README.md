# Teclado programador

He organizado las teclas que mas uso como programador de aplicaciones. Cualquier sugerencia es bienvenida

##  Capa 1

Capa basica de letras y caracteres principales para programar

![Capa basica](https://github.com/JairoGC/qmk_firmware/blob/desarrollo/keyboards/crkbd/keymaps/jailux/assets/c11.png)

##  Capa 2

Capa de funciones y caracteres mas usados. He decidido repetir la letra Z para poder usar algunos comandos del editor Vim, sobre todo con git.

![Funciones y caracteres mas usados](https://github.com/JairoGC/qmk_firmware/blob/desarrollo/keyboards/crkbd/keymaps/jailux/assets/c22.png)

##  Capa 3

Capa numérica y control de audio y video

![Capa numerica y control de audio](https://github.com/JairoGC/qmk_firmware/blob/desarrollo/keyboards/crkbd/keymaps/jailux/assets/c33.png)

##  Capa 4

Capa extra

![Capa extra](https://github.com/JairoGC/qmk_firmware/blob/desarrollo/keyboards/crkbd/keymaps/jailux/assets/c44.png)

# Instalacion

## Configurar qmk

- qmk config user.keyboard=crkbd
- qmk config user.keymap=jailux

## Compilar 

- qmk compile

## Flashing

- sudo dfu-programmer atmega32u4 erase --force
- sudo dfu-programmer atmega32u4 flash crkbd_rev1_legacy_jailux.hex
- sudo dfu-programmer atmega32u4 reset
