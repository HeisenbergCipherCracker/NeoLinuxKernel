
#ifdef MAIN
#ifdef VERSION_STRINGS
static BYTE *clock_hRcsId =
    "$Id: clock.h 485 2002-12-09 00:17:15Z bartoldeman $";
#endif
#endif

struct ClockRecord {
  UWORD clkDays;                /* days since Jan 1, 1980.              */
  UBYTE clkMinutes;             /* residual minutes.                    */
  UBYTE clkHours;               /* residual hours.                      */
  UBYTE clkHundredths;          /* residual hundredths of a second.     */
  UBYTE clkSeconds;             /* residual seconds.                    */
};
