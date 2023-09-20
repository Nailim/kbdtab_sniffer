#include <u.h>
#include <libc.h>
#include <keyboard.h>


static int mod;


static int
processkbd(char *s)
{
fprint(2, "\n");

	/* process keyboard input */
	/* inspired by riow and shortcuts */

	char b[128], *p;
	int n, o, skip;
	Rune r;

	o = 0;
	b[o++] = *s;


	fprint(2, "processkbd: *s %d\n", *s);

	/* mod key */
	if(*s == 'k' || *s == 'K'){
		fprint(2, "processkbd - mod key: *s+1 %d\n", *s+1);
		mod = 0;
		if(utfrune(s+1, Kctl) != nil){
			fprint(2, "processkbd - mod key: CTRL\n");
			mod |= Kctl;
		}
	}


	fprint(2, "processkbd - mod raw: %d\n", mod);

	for(p = s+1; *p != 0; p += n){
		if((n = chartorune(&r, p)) == 1 && r == Runeerror){
			/* bail out */
			fprint(2, "processkbd - for: bail out\n");
			n = strlen(p);
			memmove(b+o, p, n);
			o += n;
			break;
		}

		fprint(2, "processkbd - for: chartorune n %d\n", n);


		fprint(2, "processkbd - for: r %d\n", r);


		skip = 0;

		/* react to character input - test what goues on in the background */
		if(*s == 'c'){
			fprint(2, "processkbd - for: if *s == c\n");
			/* react */
			if(mod == Kctl){
				fprint(2, "processkbd - for: if *s == c AND mod == Kctl\n");
				if(r == Kup){
					fprint(2, "processkbd - for: if *s == c & mod == Kctl & r == Kup\n");
					skip = 1;
				}
				if(r == Kdown){
					fprint(2, "processkbd - for: if *s == c AND mod == Kctl AND r == Kup\n");
					skip = 1;
				}
			}

			/* if command entered or canceled */
			if(r == 10 || r == 127){
				/* 10 - enter key */
				/* 127 - delete key */
				fprint(2, "processkbd - react: RESET (ENTER / DELETE)\n");
			}
		}
		/* react to kontrol input - test what goues on in the background */
		if(*s == 'k'){
			fprint(2, "processkbd - for: if *s == k\n");
			/* react */
			if(mod == Kctl){
				fprint(2, "processkbd - for: if *s == k AND mod == Kctl\n");
				if(r == Kup){
					fprint(2, "processkbd - for: if *s == k & mod == Kctl & r == Kup\n");
					skip = 1;
				}
				if(r == Kdown){
					fprint(2, "processkbd - for: if *s == k AND mod == Kctl AND r == Kup\n");
					skip = 1;
				}
			}

			/* if command entered or canceled */
			if(r == 10 || r == 127){
				/* 10 - enter key */
				/* 127 - delete key */
				fprint(2, "processkbd - react: RESET (ENTER / DELETE)\n");
			}
		}

		if(!skip){
			fprint(2, "processkbd - react: SEND FORWARD!\n");
			memmove(b+o, p, n);
			o += n;
		}
	}

	/* move the keyboard chars along to the next one in the chain */
	b[o++] = 0;
	return (o > 1 && write(1, b, o) <= 0) ? -1 : 0;
}


static void
usage(void)
{
	fprint(2, "usage: %s \n", argv0);
	exits("usage");
}


void
main(int argc, char **argv)
{

	fprint(2, "starting kbdtab_sniffer ...\n");
	fprint(2, "processkbd: Kctl value: %d\n", Kctl);
	fprint(2, "processkbd: Kup value: %d\n", Kup);
	fprint(2, "processkbd: Kdown value: %d\n", Kdown);

	ARGBEGIN{
	default:
		usage();
	}ARGEND


	char b[128];
	int n;

	for(;;){
		if((n = read(0, b, sizeof(b)-1)) <= 0){
			break;
		}

		b[n] = 0;

		if(processkbd(b) != 0) {
			break;
		}
	}

	exits(nil);
}
