all: multiline oneline print-dates
clean:
	rm -f multiline oneline
.PHONY: all clean

multiline: multiline.c
	${CC} -o $@ $?
oneline: oneline.c
	${CC} -o $@ $?
print-dates: print-dates.c
	${CC} -o $@ $?

