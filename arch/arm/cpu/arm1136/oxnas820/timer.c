#include <common.h>
#include <asm/arch/ox820/regs.h>

#define TIMER_LOAD_VAL 0xffffUL
#define READ_TIMER ((*(volatile ushort *)(CFG_TIMERBASE+4)) & 0xFFFFUL)  /* RPS timer value register has only 16 defined bits */

#define CFG_HZ                   ((RPSCLK) / 16) 

static ulong timestamp;
static ulong lastdec;

int timer_init(void)
{
    // Setup timer 1 load value
    *(volatile ulong*)(CFG_TIMERBASE + 0) = TIMER_LOAD_VAL;

    // Setup timer 1 prescaler, periodic operation and start it
    *(volatile ulong*)(CFG_TIMERBASE + 8) =
        (TIMER_PRESCALE_ENUM << TIMER_PRESCALE_BIT) |
        (TIMER_MODE_PERIODIC << TIMER_MODE_BIT) |
        (TIMER_ENABLE_ENABLE << TIMER_ENABLE_BIT);
    
	/* init the timestamp and lastdec value */
	reset_timer_masked();
    
    return 0;
}

/*
 * timer without interrupts
 */

void reset_timer (void)
{
	reset_timer_masked ();
}

ulong get_timer (ulong base)
{
	return get_timer_masked () - base;
}

void set_timer (ulong t)
{
	timestamp = t;
}

/* delay x useconds AND perserve advance timstamp value */
void __udelay (unsigned long usec)
{
	ulong tmo, tmp;

	if(usec >= 1000){               /* if "big" number, spread normalization to seconds */
		tmo = usec / 1000;      /* start to normalize for usec to ticks per sec */
		tmo *= CFG_HZ;          /* find number of "ticks" to wait to achieve target */
		tmo /= 1000;            /* finish normalize. */
	}else{                          /* else small number, don't kill it prior to HZ multiply */
		tmo = usec * CFG_HZ;
		tmo /= (1000*1000);
	}

	tmp = get_timer (0);		/* get current timestamp */
	if( (tmo + tmp + 1) < tmp ) 	/* if setting this fordward will roll time stamp */
		reset_timer_masked ();	/* reset "advancing" timestamp to 0, set lastdec value */
	else
		tmo += tmp;		/* else, set advancing stamp wake up time */

	while (get_timer_masked () < tmo)/* loop till event */
		/*NOP*/;
}

void reset_timer_masked (void)
{
	/* reset time */
	lastdec = READ_TIMER;  /* capure current decrementer value time */
	timestamp = 0;         /* start "advancing" time stamp from 0 */
}

ulong get_timer_masked (void)
{
	ulong now = READ_TIMER;		/* current tick value */

	if (lastdec >= now) {		/* normal mode (non roll) */
		/* normal mode */
		timestamp += lastdec - now; /* move stamp fordward with absoulte diff ticks */
	} else {			/* we have overflow of the count down timer */
		/* nts = ts + ld + (TLV - now)
		 * ts=old stamp, ld=time that passed before passing through -1
		 * (TLV-now) amount of time after passing though -1
		 * nts = new "advancing time stamp"...it could also roll and cause problems.
		 */
		timestamp += lastdec + TIMER_LOAD_VAL - now;
	}
	lastdec = now;

	return timestamp;
}

/* waits specified delay value and resets timestamp */
void udelay_masked (unsigned long usec)
{
	ulong tmo;

	if(usec >= 1000){               /* if "big" number, spread normalization to seconds */
		tmo = usec / 1000;      /* start to normalize for usec to ticks per sec */
		tmo *= CFG_HZ;          /* find number of "ticks" to wait to achieve target */
		tmo /= 1000;            /* finish normalize. */
	}else{                          /* else small number, don't kill it prior to HZ multiply */
		tmo = usec * CFG_HZ;
		tmo /= (1000*1000);
	}

	reset_timer_masked ();	/* set "advancing" timestamp to 0, set lastdec vaule */

	while (get_timer_masked () < tmo) /* wait for time stamp to overtake tick number.*/
		/*NOP*/;
}

/*
 * This function is derived from PowerPC code (read timebase as long long).
 * On ARM it just returns the timer value.
 */
unsigned long long get_ticks(void)
{
	return get_timer(0);
}

/*
 * This function is derived from PowerPC code (timebase clock frequency).
 * On ARM it returns the number of timer ticks per second.
 */
ulong get_tbclk (void)
{
	ulong tbclk;

	tbclk = CFG_HZ;
	return tbclk;
}
