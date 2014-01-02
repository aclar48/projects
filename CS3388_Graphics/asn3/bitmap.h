/* Windows BMP file definition an manipulation for OpenGL.
 
   Written by Michael Sweet
   Extended to C++ by Grzegorz Wierzowiecki
   Modified by Steven Beauchemin                                          */

#ifndef MSWEET_BITMAP_H_
#define MSWEET_BITMAP_H_

#ifdef WIN32
  #include <windows.h>
  #include <wingdi.h>
#endif 
                 /* Make this header file work with C and C++ source code */
#ifdef __cplusplus
  extern "C" {
#endif
    /* Bitmap file data structures (these are defined in <wingdi.h> under
                                                                  Windows
   Note that most Windows compilers will pack the following structures so
   for reading them under MacOS or UNIX we need to read individual fields
                                      to avoid differences in alignment.  */

#ifndef WIN32
typedef struct {                             /* BMP file header structure */
  unsigned short bfType ;                        /* Magic number for file */
  unsigned int   bfSize ;                                 /* Size of file */
  unsigned short bfReserved1 ;                                /* Reserved */
  unsigned short bfReserved2 ;     
  unsigned int   bfOffBits ;                     /* Offset to bitmap data */
} BITMAPFILEHEADER ;

#define BF_TYPE 0x4D42                                              /* MB */

typedef struct {                               /* BMP file info structure */
  unsigned int   biSize  ;                         /* Size of info header */
  int            biWidth ;                              /* Width of image */
  int            biHeight ;                            /* Height of image */
  unsigned short biPlanes ;                     /* Number of color planes */
  unsigned short biBitCount ;                 /* Number of bits per pixel */
  unsigned int   biCompression ;            /* Type of compression to use */
  unsigned int   biSizeImage ;                      /* Size of image data */
  int            biXPelsPerMeter ;                  /* X pixels per meter */
  int            biYPelsPerMeter ;                  /* Y pixels per meter */
  unsigned int   biClrUsed ;                     /* Number of colors used */
  unsigned int   biClrImportant ;           /* Number of important colors */
} BITMAPINFOHEADER;

                                 /* Constants for the biCompression field */

#define BI_RGB       0              /* No compression - straight BGR data */
#define BI_RLE8      1                    /* 8-bit run-length compression */
#define BI_RLE4      2                    /* 4-bit run-length compression */
#define BI_BITFIELDS 3                       /* RGB bitmap with RGB masks */

typedef struct {                              /* Colormap entry structure */
  unsigned char rgbBlue ;                                   /* Blue value */
  unsigned char rgbGreen ;                                 /* Green value */
  unsigned char rgbRed ;                                     /* Red value */
  unsigned char rgbReserved ;                                 /* Reserved */
} RGBQUAD ;

typedef struct {                          /* Bitmap information structure */
  BITMAPINFOHEADER bmiHeader ;                            /* Image header */
  RGBQUAD          bmiColors[256] ;                     /* Image colormap */
} BITMAPINFO;
#endif 

#  ifdef __cplusplus
}

                                   /* Grzegorz Wierzowiecki C++ extension */
class bitmap { public:
  BITMAPINFO info ;
  GLubyte *bits ;
  bool own_buf ;
  bitmap() ;
  ~bitmap() ;
  void init(BITMAPINFO info, GLubyte *bits) ; 
  void init(int w, int h) ;
  void erase() ;
  void put(int x, int y, GLubyte r, GLubyte g, GLubyte b) ;
  void get(int x, int y, GLubyte &r, GLubyte &g, GLubyte &b) ;
} ;
                            /* End of Grzegorz Wierzowiecki C++ Extension */

#endif /* __cplusplus */
#endif /* !_BITMAP_H_ */

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else 
  #include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifdef __cplusplus
  extern "C" {
#endif

#ifdef WIN32
/* LoadDIBitmap()  - Load a DIB/BMP file from disk.  Returns a pointer to 
                                the bitmap if successful, NULL otherwise. */

GLubyte *LoadDIBitmap(const char *filename,BITMAPINFO **info) {                

  FILE             *fp ;                             /* Open file pointer */
  GLubyte          *bits ;                           /* Bitmap pixel bits */
  int              bitsize ;                            /* Size of bitmap */
  int              infosize ;               /* Size of header information */
  BITMAPFILEHEADER header ;                                /* File header */

       /* Try opening the file; use "rb" mode to read this *binary* file. */
  if ((fp = fopen(filename, "rb")) == NULL)
    return (NULL) ;
            /* Read the file header and any following bitmap information. */
  if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
                          /* Couldn't read the file header - return NULL. */
    fclose(fp) ;
    return (NULL) ;
  }

  if (header.bfType != 'MB') {                  /* Check for BM reversed. */
                                      /* Not a bitmap file - return NULL. */
    fclose(fp) ;
    return (NULL) ;
  }

  infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
  if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
               /* Couldn't allocate memory for bitmap info - return NULL. */
    fclose(fp) ;
    return (NULL) ;
  }

  if (fread(*info, 1, infosize, fp) < infosize) {
                        /* Couldn't read the bitmap header - return NULL. */
    free(*info) ;
    fclose(fp) ;
    return (NULL) ;
  }

     /* Now that we have all the header info read in, allocate memory for 
                                                the bitmap and read it in */
  if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
    bitsize = ((*info)->bmiHeader.biWidth *(*info)->bmiHeader.biBitCount + 7)/8*abs((*info)->bmiHeader.biHeight) ;

  if ((bits = malloc(bitsize)) == NULL) {
                               /* Couldn't allocate memory - return NULL. */
    free(*info) ;
    fclose(fp) ;
    return (NULL) ;
  }

  if (fread(bits, 1, bitsize, fp) < bitsize) {
                   /* Couldn't read bitmap - free memory and return NULL. */
    free(*info) ;
    free(bits) ;
    fclose(fp) ;
    return (NULL) ;
  }

                   /* Everything went fine - return the allocated bitmap. */
  fclose(fp) ;
  return (bits) ;
}


                       /* SaveDIBitmap()' - Save a DIB/BMP file to disk.
                                  Returns 0 on success or -1 on failure.  */

int SaveDIBitmap(const char *filename,BITMAPINFO *info,GLubyte *bits) {

  FILE *fp ;                                         /* Open file pointer */
  int  size,                                              /* Size of file */
       infosize,                                   /* Size of bitmap info */
       bitsize ;                                 /* Size of bitmap pixels */
  BITMAPFILEHEADER header ;                                /* File header */

        /* Try opening the file; use "wb" mode to write this binary file. */
  if ((fp = fopen(filename, "wb")) == NULL)
    return (-1) ;

                                           /* Figure out the bitmap size. */
  if (info->bmiHeader.biSizeImage == 0)
      bitsize = (info->bmiHeader.biWidth*info->bmiHeader.biBitCount + 7)/8*abs(info->bmiHeader.biHeight) ;
  else
      bitsize = info->bmiHeader.biSizeImage ;

                                           /* Figure out the header size. */
  infosize = sizeof(BITMAPINFOHEADER) ;
  switch (info->bmiHeader.biCompression) {
    case BI_BITFIELDS :
      infosize += 12 ;                      /* Add 3 RGB doubleword masks */
      if (info->bmiHeader.biClrUsed == 0)
        break ;
    case BI_RGB :
      if (info->bmiHeader.biBitCount > 8 &&
        info->bmiHeader.biClrUsed == 0)
          break ;
    case BI_RLE8 :
    case BI_RLE4 :
      if (info->bmiHeader.biClrUsed == 0)
        infosize += (1 << info->bmiHeader.biBitCount) * 4 ;
      else
        infosize += info->bmiHeader.biClrUsed * 4 ;
      break ;
  }

  size = sizeof(BITMAPFILEHEADER) + infosize + bitsize ;
     /* Write the file header, bitmap information, and bitmap pixel data. */
  header.bfType = 'MB' ;                                  /* Non-portable */
  header.bfSize = size ;
  header.bfReserved1 = 0 ;
  header.bfReserved2 = 0 ;
  header.bfOffBits = sizeof(BITMAPFILEHEADER) + infosize ;

  if (fwrite(&header,1,sizeof(BITMAPFILEHEADER),fp) < sizeof(BITMAPFILEHEADER)) {
                              /* Couldn't write the file header - return. */
    fclose(fp) ;
    return (-1) ;
  }

  if (fwrite(info, 1, infosize, fp) < infosize) {
                            /* Couldn't write the bitmap header - return. */
    fclose(fp) ;
    return (-1) ; 
  }

  if (fwrite(bits, 1, bitsize, fp) < bitsize) {
                                   /* Couldn't write the bitmap - return. */
    fclose(fp) ;
    return (-1) ;
  }
                                        /* Everything went fine - return. */
  fclose(fp) ;
  return (0) ;
}


#else /* !WIN32 */
/* Functions for reading and writing 16 and 32-bit little-endian integers */

static unsigned short read_word(FILE *fp) ;
static unsigned int read_dword(FILE *fp) ;
static int read_long(FILE *fp) ;

static int write_word(FILE *fp,unsigned short w) ;
static int write_dword(FILE *fp,unsigned int dw) ;
static int write_long(FILE *fp,int l) ;

                         /* LoadDIBitmap() Load a DIB/BMP file from disk.
           Returns a pointer to the bitmap if successful, NULL otherwise. */

GLubyte *LoadDIBitmap(const char *filename,BITMAPINFO **info) {

  FILE *fp ;                                         /* Open file pointer */
  GLubyte *bits ;                                    /* Bitmap pixel bits */
  GLubyte *ptr ;                                   /* Pointer into bitmap */
  GLubyte temp ;               /* Temporary variable to swap red and blue */
  int x, y ;                                 /* X and Y position in image */
  int length ;                                             /* Line length */
  int bitsize ;                                         /* Size of bitmap */
  int infosize ;                            /* Size of header information */
  BITMAPFILEHEADER header ;                                /* File header */

         /* Try opening the file; use "rb" mode to read this binary file. */
  if ((fp = fopen(filename,"rb")) == NULL)
    return (NULL) ;

            /* Read the file header and any following bitmap information. */
  header.bfType = read_word(fp) ;
  header.bfSize = read_dword(fp) ;
  header.bfReserved1 = read_word(fp) ;
  header.bfReserved2 = read_word(fp) ;
  header.bfOffBits = read_dword(fp) ;

  if (header.bfType != BF_TYPE) {               /* Check for BM reversed. */
                                      /* Not a bitmap file - return NULL. */
    fclose(fp) ;
    return (NULL) ;
  }

  infosize = header.bfOffBits - 18 ;
  if ((*info = (BITMAPINFO *)malloc(sizeof(BITMAPINFO))) == NULL) {
               /* Couldn't allocate memory for bitmap info - return NULL. */
    fclose(fp) ;
    return (NULL) ;
  }

  (*info)->bmiHeader.biSize = read_dword(fp) ;
  (*info)->bmiHeader.biWidth = read_long(fp) ;
  (*info)->bmiHeader.biHeight = read_long(fp) ;
  (*info)->bmiHeader.biPlanes = read_word(fp) ;
  (*info)->bmiHeader.biBitCount = read_word(fp) ;
  (*info)->bmiHeader.biCompression = read_dword(fp) ;
  (*info)->bmiHeader.biSizeImage = read_dword(fp) ;
  (*info)->bmiHeader.biXPelsPerMeter = read_long(fp) ;
  (*info)->bmiHeader.biYPelsPerMeter = read_long(fp) ;
  (*info)->bmiHeader.biClrUsed = read_dword(fp) ;
  (*info)->bmiHeader.biClrImportant = read_dword(fp) ;

  if (infosize > 40)
    if (fread((*info)->bmiColors,infosize - 40,1,fp) < 1) {
                        /* Couldn't read the bitmap header - return NULL. */
      free(*info) ;
      fclose(fp) ;
      return (NULL) ;
    }

    /* Now that we have all the header info read in, allocate memory for
                                               the bitmap and read it in. */
  if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
      bitsize = ((*info)->bmiHeader.biWidth *(*info)->bmiHeader.biBitCount+7)/8*abs((*info)->bmiHeader.biHeight) ;
  if ((bits = (GLubyte *)malloc(bitsize)) == NULL) {
                               /* Couldn't allocate memory - return NULL. */
    free(*info) ;
    fclose(fp) ;
    return (NULL) ;
  }

  if (fread(bits,1,bitsize,fp) < bitsize) {
                   /* Couldn't read bitmap - free memory and return NULL. */
    free(*info) ;
    free(bits) ;
    fclose(fp) ;
    return (NULL) ;
  }
                                                     /* Swap red and blue */
  length = ((*info)->bmiHeader.biWidth*3+3) & ~3 ;
  for (y = 0; y < (*info)->bmiHeader.biHeight; y ++) {
    for (ptr = bits+y*length, x = (*info)->bmiHeader.biWidth ; x > 0; x --, ptr += 3) {
      temp   = ptr[0] ;
      ptr[0] = ptr[2] ;
      ptr[2] = temp ;
    }
  }
                   /* Everything went fine - return the allocated bitmap. */
  fclose(fp) ;
  return (bits) ;
}

 /* SaveDIBitmap() - Save a DIB/BMP file to disk. Returns 0 on success or
                                                           -1 on failure. */

int SaveDIBitmap(const char *filename,BITMAPINFO *info,GLubyte *bits) {

  FILE *fp ;                                         /* Open file pointer */
  int  size,                                              /* Size of file */
       infosize,                                   /* Size of bitmap info */
       bitsize ;                                 /* Size of bitmap pixels */

        /* Try opening the file; use "wb" mode to write this binary file. */
  if ((fp = fopen(filename, "wb")) == NULL)
    return (-1) ;
                                            /* Figure out the bitmap size */
  if (info->bmiHeader.biSizeImage == 0)
    bitsize = (info->bmiHeader.biWidth*info->bmiHeader.biBitCount+7)/8*abs(info->bmiHeader.biHeight) ;
  else
    bitsize = info->bmiHeader.biSizeImage ;

                                            /* Figure out the header size */
  infosize = sizeof(BITMAPINFOHEADER) ;
  switch (info->bmiHeader.biCompression) {
    case BI_BITFIELDS :
      infosize += 12 ; /* Add 3 RGB doubleword masks */
      if (info->bmiHeader.biClrUsed == 0)
        break ;
    case BI_RGB :
      if (info->bmiHeader.biBitCount > 8 && info->bmiHeader.biClrUsed == 0)
        break ;
    case BI_RLE8 :
    case BI_RLE4 :
      if (info->bmiHeader.biClrUsed == 0)
         infosize += (1 << info->bmiHeader.biBitCount)*4 ;
      else
        infosize += info->bmiHeader.biClrUsed*4 ;
      break ;
    }

  size = sizeof(BITMAPFILEHEADER) + infosize + bitsize ;
     /* Write the file header, bitmap information, and bitmap pixel data. */
  write_word(fp, BF_TYPE) ;                                     /* bfType */
  write_dword(fp, size) ;                                       /* bfSize */
  write_word(fp, 0) ;                                      /* bfReserved1 */
  write_word(fp, 0) ;                                      /* bfReserved2 */
  write_dword(fp, 18 + infosize) ;                           /* bfOffBits */

  write_dword(fp, info->bmiHeader.biSize) ;
  write_long(fp, info->bmiHeader.biWidth) ;
  write_long(fp, info->bmiHeader.biHeight) ;
  write_word(fp, info->bmiHeader.biPlanes) ;
  write_word(fp, info->bmiHeader.biBitCount) ;
  write_dword(fp, info->bmiHeader.biCompression) ;
  write_dword(fp, info->bmiHeader.biSizeImage) ;
  write_long(fp, info->bmiHeader.biXPelsPerMeter) ;
  write_long(fp, info->bmiHeader.biYPelsPerMeter) ;
  write_dword(fp, info->bmiHeader.biClrUsed) ;
  write_dword(fp, info->bmiHeader.biClrImportant) ;

  if (infosize > 40)
    if (fwrite(info->bmiColors,infosize - 40,1,fp) < 1) {
                            /* Couldn't write the bitmap header - return. */
      fclose(fp);
      return(-1);
    }

  if (fwrite(bits, 1, bitsize, fp) < bitsize) {
                                   /* Couldn't write the bitmap - return. */
    fclose(fp) ;
    return (-1) ;
  }

                                        /* Everything went fine - return. */
  fclose(fp) ;
  return (0) ;
}


                         /* read_word() - Read a 16-bit unsigned integer. */
static unsigned short read_word(FILE *fp) {

  unsigned char b0, b1 ;                               /* Bytes from file */

  b0 = getc(fp) ;
  b1 = getc(fp) ;
  return ((b1 << 8) | b0) ;
}


                        /* read_dword() - Read a 32-bit unsigned integer. */
static unsigned int read_dword(FILE *fp) {

  unsigned char b0, b1, b2, b3 ;                       /* Bytes from file */

  b0 = getc(fp) ;
  b1 = getc(fp) ;
  b2 = getc(fp) ;
  b3 = getc(fp) ;
  return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0) ;
}

                          /* read_long()' - Read a 32-bit signed integer. */
static int read_long(FILE *fp) {

  unsigned char b0, b1, b2, b3 ;                       /* Bytes from file */

  b0 = getc(fp) ;
  b1 = getc(fp) ;
  b2 = getc(fp) ;
  b3 = getc(fp) ;
  return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0) ;
}

                       /* write_word() - Write a 16-bit unsigned integer. */

static int write_word(FILE *fp,unsigned short w) {

  putc(w, fp) ;
  return (putc(w >> 8,fp)) ;
}

                      /* write_dword() - Write a 32-bit unsigned integer. */
static int write_dword(FILE *fp,unsigned int dw) {

  putc(dw, fp) ;
  putc(dw >> 8, fp) ;
  putc(dw >> 16, fp) ;
  return (putc(dw >> 24,fp)) ;
}

                         /* write_long() - Write a 32-bit signed integer. */
static int write_long(FILE *fp,int l) {

  putc(l, fp) ;
  putc(l >> 8, fp) ;
  putc(l >> 16, fp) ; 
  return (putc(l >> 24,fp)) ;
}

#ifdef __cplusplus
};

                                  /* Grzegorz Wierzowiecki C++ extension */

bitmap::bitmap():own_buf(false),bits(NULL){} ;
bitmap::~bitmap(){ erase() ; } ;

void bitmap::init(BITMAPINFO info,GLubyte *bits) {
  erase() ;
  this->info = info ;
  this->bits = bits ;
  own_buf = false ;
} ; 

void bitmap::init(int w,int h) {
  erase() ;
  info.bmiHeader.biWidth = (w+3) & ~3 ;
  info.bmiHeader.biHeight = h ;
  own_buf = true ;
  bits = new GLubyte[w*h*3] ;
  memset((void *)bits, 0, w*h*3) ;
} ;

void bitmap::erase() {
  if(own_buf) if(bits) delete bits ;
  own_buf = false; bits=NULL ;
} ;

void bitmap::put(int x,int y,GLubyte r,GLubyte g,GLubyte b) {
  int width = info.bmiHeader.biWidth ;
  // width = (width+3) & ~3 ;  // 4B aligment
  bits[ (y * width + x)*3 + 0] = r ;
  bits[ (y * width + x)*3 + 1] = g ;
  bits[ (y * width + x)*3 + 2] = b ;
} ;

void bitmap::get(int x,int y,GLubyte &r,GLubyte &g,GLubyte &b) {
  int width = info.bmiHeader.biWidth ;
  // width = (width+3) & ~3 ;  // 4B aligment
  r = bits[ (y * width + x)*3 + 0] ;
  g = bits[ (y * width + x)*3 + 1] ;
  b = bits[ (y * width + x)*3 + 2] ;
} ;

#endif /* __cplusplus */
#endif /* WIN32 */
