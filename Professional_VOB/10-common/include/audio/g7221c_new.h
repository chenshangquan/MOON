/*****************************************************************************
ģ   ��   ��: g7221 Annex c��������ӿ�
��   ��   ��: g7221c_new.h
�� ��  �� ��: decode.c,encode.c
�ļ�ʵ�ֹ���: 
��        ��: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
 2006/05/09      1.0         ��  ��      ��    ��
 2007/11/26      2.0         ��  ��      ����鵽����ĸı�
******************************************************************************/

#ifndef G7221C_H
#define G7221C_H

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************************
 Constant definitions                                                    
*************************************************************************************/
#define G7221C_FRAMESIZE      640
#define G7221_FRAMESIZE       320

#define MAX_SAMPLE_RATE 32000
#define MAX_FRAMESIZE   (MAX_SAMPLE_RATE/50)

#define FRAMESIZE MAX_FRAMESIZE
#define MAX_WORD_PER_FRAME  (MAX_BITS_PER_FRAME/16)

//#define G7221C_BITRATE	 24000  //24000 or 32000 or 48000
#define G7221C_BANDWITH  14000

#define G7221_BITRATE	 24000  //24000 or 32000
#define G7221_BANDWITH   7000 

#define MAX_DCT_LENGTH      640
#define MAX_BITS_PER_FRAME  960

#define G7221_BITRATE_ERR   (-2)
#define G7221_MALLOC_ERR    (-1)
#define G7221_OK            1


typedef enum SyntaxType
{
	PACKED_FORMAT,  //packed bitstream
	ITU192_FORMAT   //ITU selection test bitstream
}CodeFormat;

//enoder...
typedef struct 
{
    s16  syntax;
    l32  bit_rate;
    s16  bandwidth;  
    s16  number_of_bits_per_frame; 
    s16  number_of_regions; 
    s16  frame_size;

    s16  history[MAX_FRAMESIZE];
    s16  mlt_coefs[MAX_FRAMESIZE];


	/////////////
	s16	as16WindowedData[640]; //MAX_DCT_LENGTH

    s16  absolute_region_power_index[28];
    s16  power_categories[28];
    s16  category_balances[32];
    s16  drp_num_bits[30];
    u16  drp_code_bits[30];
    s16  region_mlt_bit_counts[28];
    u32  region_mlt_bits[4*28];

} TG7221CEncoder;

void  GetG7221cVersion(s8 *Version, l32 StrLen, l32 * StrLenUsed);
void g7221_encfree(void *pvG7221EncH);
s16 g7221_encinit(void **ppvEncH, l32 l32BitRate);
void g7221_encode(void *pvEncH, s16 *ps16InBuf, s16 *ps16OutBuf);

//2006-12-27 add
void g7221_encinit_TI(void *pvEncH, l32 l32BitRate);

//decoder...

/***************************************************************************/
/* Type definitions                                                        */
/***************************************************************************/
typedef struct
{
    s16 *code_word_ptr;      /* pointer to the bitstream */
    s16 code_bit_count;      /* bit count of the current word */
    s16 current_word;        /* current word in the bitstream being processed */
    s16 number_of_bits_left; /* number of bits left in the current word */
    s16 next_bit;            /* next bit in the current word */
}Bit_Obj;

typedef struct
{
    s16 seed0;
    s16 seed1;
    s16 seed2;
    s16 seed3;
}Rand_Obj;


/* This object is used to control the command line input */
typedef struct 
{
    s16  syntax;
    l32  bit_rate;
    s16  bandwidth;
    s16  number_of_bits_per_frame;
    s16  number_of_regions;
    s16  frame_size;

    s16 frame_error_flag;
    s16 mag_shift;
    s16 old_mag_shift;

    Rand_Obj randobj;
    Bit_Obj bitobj;

	//buf
    s16 decoder_mlt_coefs[MAX_DCT_LENGTH];
    s16 old_decoder_mlt_coefs[MAX_DCT_LENGTH];
    s16 old_samples[MAX_DCT_LENGTH>>1];

	///////////////////////////////
    s16  absolute_region_power_index[28];
    s16  decoder_power_categories[28];
    s16  decoder_category_balances[32];
    s16  decoder_region_standard_deviation[28];

	s16	new_samples[640];


}TG7221CDecoder;


s16 g7221_decinit(void **ppDecH, l32 l32BitRate);
void g7221_decfree(void *pDecH);
void g7221_decode(void *pDecH, s16 *ps16InBuf, s16 *ps16OutBuf);

void g7221_decinit_TI(void *ppDecH, l32 l32BitRate);


#ifdef __cplusplus
}
#endif


#endif //end of G7221C_H

