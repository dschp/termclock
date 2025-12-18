all: multiline oneline print-dates streamclock
clean:
	rm -f multiline oneline print-dates streamclock
.PHONY: all clean

multiline: multiline.c
	${CC} -o $@ $<
oneline: oneline.c
	${CC} -o $@ $<
print-dates: print-dates.c
	${CC} -o $@ $<
streamclock: streamclock.c
	${CC} -o $@ $<

