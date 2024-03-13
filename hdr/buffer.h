#ifdef MAIN
#ifdef VERSION_STRINGS
static BYTE *buffer_hRcsId =
    "$Id: buffer.h 1702 2012-02-04 08:46:16Z perditionc $";
#endif
#endif

#include "dsk.h"                /* only for MAX_SEC_SIZE        */
#define BUFFERSIZE MAX_SEC_SIZE

struct buffer {
  UWORD b_next;                 /* next buffer in LRU list      */
  UWORD b_prev;                 /* previous buffer in LRU list  */
  BYTE b_unit;                  /* disk for this buffer         */
  BYTE b_flag;                  /* buffer flags                 */
  ULONG b_blkno;                /* block for this buffer        */
  UBYTE b_copies;               /* number of copies to write    */
  UWORD b_offset;               /* offset in sectors between copies
                                   to write for FAT sectors     */
  struct dpb FAR *b_dpbp;       /* pointer to DPB               */
  UWORD b_remotesz;             /* size of remote buffer if remote */
  BYTE b_padding;
  UBYTE b_buffer[BUFFERSIZE];   /* 512 byte sectors for now     */
};

#define BFR_DIRTY       0x40    /* buffer modified              */
#define BFR_VALID       0x20    /* buffer contains valid data   */
#define BFR_DATA        0x08    /* buffer is from data area     */
#define BFR_DIR         0x04    /* buffer is from dir area      */
#define BFR_FAT         0x02    /* buffer is from fat area      */
#define BFR_UNCACHE     0x01    /* buffer to be released ASAP   */
