
building .elf file:
just run 'make'

flashing to the board:
in one terminal run st-util and keep open

in a second termal run 'arm-none-eabi-gdb fancyblink.elf'
(gdb) tar extended-remote :4242
(gdb) load