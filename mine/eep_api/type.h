/*=======================================================
<<<<<<<<<<<<<<<<<<< Collect By Jack >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
---------------------------------------------------------
               All right reserved.2019.07
---------------------------------------------------------
 file name: type.h
 desc: defined some common use data type for convinient use
 author: ?
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#ifndef __TYPE_H__
#define __TYPE_H__

/* define boolean type */
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/* define common used number type */
typedef unsigned char  	uint8;                   /* 无符号8位整型变量       */
typedef signed   char  	int8;                    /* 有符号8位整型变量       */
typedef unsigned int   	uint16;                  /* 无符号16位整型变量      */
typedef signed   int   	int16;                   /* 有符号16位整型变量      */
typedef unsigned long  	uint32;                  /* 无符号32位整型变量      */
typedef signed   long  	int32;                   /* 有符号32位整型变量      */
typedef float           fp32;                    /* 单精度浮点数（32位长度）*/
typedef double          fp64;                    /* 双精度浮点数（64位长度）*/

#endif