call nasm -f bin -I bootloader\ -o bin\boot2.bin bootloader\boot2.asm
REM call nasm -f bin -o boot.bin boot.asm
call disktk -o image.bin -w bin\boot2.bin boot2.bin