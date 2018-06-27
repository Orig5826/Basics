#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

//  BOOL
typedef enum _BOOL
{
	FALSE = 0,
	TRUE
}BOOL;
#if 0
typedef uint8_t 			BOOL;
#ifndef TRUE
#define TRUE				1
#endif
#ifndef FALSE
#define FALSE				0
#endif
#endif

// NULL
#define  NULL 	((void *)0)

#endif
