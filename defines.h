//defines.h
#define WRITEBYTE(WORD,STARTBIT,BYTE) \
        WORD=((WORD&~(0xFF<<STARTBIT))| \
				      (BYTE<<STARTBIT))

#define READBIT(WORD,BIT) ((WORD>>BIT)&1)
#define WRITENIBBLE(WORD,BIT,DATA) \
        (WORD = (WORD & ~(15<< BIT)) | ((DATA & 15) << BIT))


#define READNIBBLE(WORD,BIT) ((WORD>>BIT)&15)


//add more as & when required for future
//reusability
