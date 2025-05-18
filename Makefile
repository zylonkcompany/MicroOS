all:
	gcc -ffreestanding -m32 -fno-stack-protector -std=gnu99 -O2 entry.s -c -o entry.o
	gcc -ffreestanding -m32 -fno-stack-protector -std=gnu99 -O2 microk.c -c -o microk.o
	gcc -ffreestanding -m32 -fno-stack-protector -std=gnu99 -O2 log.c -c -o log.o
	mkdir -p isodir/boot/grub 
	ld -m elf_i386 -T linker.ld microk.o entry.o log.o -o microk.bin
	cp grub.cfg isodir/boot/grub
	cp microk.bin isodir/boot
	grub-mkrescue isodir/ -o microos.iso

	qemu-system-x86_64 -cdrom microos.iso