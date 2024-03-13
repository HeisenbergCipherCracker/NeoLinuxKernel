
#ifdef MAIN
#ifdef VERSION_STRINGS
static BYTE *dirmatch_hRcsId =
    "$Id: dirmatch.h 1415 2009-06-02 13:18:24Z bartoldeman $";
#endif
#endif

typedef struct {
  UBYTE dm_drive;
  BYTE dm_name_pat[FNAME_SIZE + FEXT_SIZE];
  UBYTE dm_attr_srch;
  UWORD dm_entry;
  CLUSTER dm_dircluster;
#ifndef WITHFAT32
  UWORD reserved;
#endif
  UWORD reserved2;

  UBYTE dm_attr_fnd;            /* found file attribute         */
  time dm_time;                 /* file time                    */
  date dm_date;                 /* file date                    */
  ULONG dm_size;                /* file size                    */
  BYTE dm_name[FNAME_SIZE + FEXT_SIZE + 2];     /* file name    */
} dmatch;