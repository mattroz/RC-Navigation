all:	receiver.out sender.out

sender.out:		../rppipe.c ../../RCC/rccore.c
				gcc -Wall sender.c ../rppipe.c ../../RCC/rccore.c -g -o ./sender.out

receiver.out:	../rppipe.c ../../RCC/rccore.c
				gcc -Wall receiver.c ../rppipe.c ../../RCC/rccore.c -g -o ./receiver.out

