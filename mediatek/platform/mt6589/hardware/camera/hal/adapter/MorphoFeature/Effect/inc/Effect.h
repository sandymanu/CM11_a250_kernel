#ifndef _EFFECT_H_
#define _EFFECT_H_

#ifdef __cplusplus
extern "C"
{
#endif

 typedef struct PARM_EFFECT
{
	    int ideal_r;
     	    int ideal_g;
     	    int ideal_b;
	    int strength;
	    int face_smallness;
	    int eye_vividness;
	    int eye_wideness;
	    int eye_sharpness;
	    int eyelash_mode;
	    int red_eye;
}PARM_EFFECT;


int Effect_Init(const char* effect_name, const char* format, int height, int width);
int Effect_Function(unsigned char *src, const char *filename, PARM_EFFECT *input_param);
int Effect_Finalize();
#ifdef __cplusplus
};
#endif

#endif
