all:	receiver.out sender.out

sender.out:		../rcpipe.c ../../RCC/rccore.c
				gcc sender.c ../rcpipe.c ../../RCC/rccore.c -g -o ./sender.out

receiver.out:	../rcpipe.c ../../RCC/rccore.c
				gcc receiver.c ../rcpipe.c ../../RCC/rccore.c -g -o ./receiver.out

