all: multiline oneline
clean:
	rm -f multiline oneline
.PHONY: all clean

multiline: multiline.c
	${CC} -o $@ $?
oneline: oneline.c
	${CC} -o $@ $?

