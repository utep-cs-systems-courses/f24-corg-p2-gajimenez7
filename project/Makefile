# makfile configuration
COMMON_OBJECTS  = main.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all:
	(cd timerLib && make install)
	project2.elf

buzzer.c: buzzer.h

main.c: buzzer.h led.h

main.o: main.c buzzer.h led.h

buzzer.o: buzzer.c buzzer.h

#additional rules for files
project2.elf: ${COMMON_OBJECTS} buzzer.o main.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

load: project2.elf
	msp430loader.sh  $^

clean: $^
	rm -f *.o *.elf
