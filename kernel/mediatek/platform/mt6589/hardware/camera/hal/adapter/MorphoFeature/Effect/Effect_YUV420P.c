#include "inc/morpho_effect_engine.h"
#include "inc/morpho_get_image_size.h"

#include "inc/morpho_effect_filtering_backlight.h"
#include "inc/morpho_effect_filtering_highcontrast.h"
#include "inc/morpho_effect_filtering_lighten.h"
#include "inc/morpho_effect_filtering_moza.h"
#include "inc/morpho_effect_filtering_partcolor.h"
#include "inc/morpho_effect_filtering_poster.h"
#include "inc/morpho_effect_filtering_pretty.h"
#include "inc/morpho_effect_filtering_relic.h"
#include "inc/morpho_effect_filtering_mona.h"
#include "inc/morpho_effect_filtering_balloon.h"
#include "inc/morpho_effect_filtering_twinkle.h"
#include "inc/morpho_effect_filtering_colorfilter.h"
#include "inc/morpho_effect_filtering_nostalgy.h"
#include "inc/morpho_effect_filtering_selectcolor.h"
#include "inc/morpho_effect_filtering_kaleidoscope.h"
#include "inc/morpho_effect_filtering_pencil.h"
#include "inc/morpho_effect_filtering_fisheye1.h"
#include "inc/morpho_effect_filtering_mirror.h"
#include "inc/morpho_effect_filtering_deblur.h"
#include "inc/morpho_effect_filtering_comic.h"
#include "inc/morpho_effect_filtering_starburst.h"
#include "inc/morpho_effect_filtering_defocus.h"
#include "inc/morpho_effect_filtering_edo.h"
#include "inc/morpho_effect_filtering_miniature.h"
#include "inc/morpho_effect_filtering_vivid.h"
#include "inc/morpho_effect_filtering_overexpose.h"
#include "inc/morpho_effect_filtering_harris.h"
#include "inc/Effect.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <android/log.h>

#define MORPHO_JNI_DEBUG

#if !defined(MORPHO_JNI_DEBUG)
#define DEBUG_LOG(...)
#else   /* MORPHO_DEBUG_LOG */
#define DEBUG_LOG(...) __android_log_print(ANDROID_LOG_ERROR,"morpho_effect", __VA_ARGS__)
#endif  /* MORPHO_DEBUG_LOG */

#define PRINT_LOG(...)    DEBUG_LOG(__VA_ARGS__)

static unsigned char *p_buffer = NULL;
static morpho_ImageData input_image = {0}, output_image = {0};
static char *p_format = NULL;
unsigned char* p_effect_name = NULL;
static morpho_EffectEngine effect_engine = {0};

#define APICALL( statement, func_name )     \
{ ret = statement; if( ret != MORPHO_OK ) PRINT_LOG( "Error in " func_name ". retcode=%08X\n", ret ); }

/* image-data memory allocation */
static void allocateImageData( morpho_ImageData *p_image, const char *p_format )
{
	int size_y = morpho_getImageSizeY( p_image->width, p_image->height, p_format );
	int size_u = morpho_getImageSizeU( p_image->width, p_image->height, p_format );
	int size_v = morpho_getImageSizeV( p_image->width, p_image->height, p_format );
	int size_uv = morpho_getImageSizeUV( p_image->width, p_image->height, p_format );
	int size_all = morpho_getImageSize( p_image->width, p_image->height, p_format );
    
	if( size_y > 0 )
	{
		if( size_u > 0 )
		{
			p_image->dat.planar.y = malloc( size_all );
			p_image->dat.planar.u = ( char * )p_image->dat.planar.y + size_y;  // reference
			p_image->dat.planar.v = ( char * )p_image->dat.planar.u + size_u;  // reference
		}
		else if( size_uv > 0 )
		{
			p_image->dat.semi_planar.y = malloc( size_all );
			p_image->dat.semi_planar.uv = ( char * )p_image->dat.semi_planar.y + size_y;
		}
	}
	else
	{
		p_image->dat.p = malloc( size_all );
	}
}

static void freeImageData( morpho_ImageData *p_image )
{
	if( p_image->dat.p != 0 )
	{
		free( p_image->dat.p );
		p_image->dat.p = 0;
	}
	else if( p_image->dat.planar.y != 0 )
	{
		free( p_image->dat.planar.y );
		p_image->dat.planar.y = 0;
		p_image->dat.planar.u = 0;
		p_image->dat.planar.v = 0;
	}
	else if( p_image->dat.semi_planar.y != 0 )
	{
		free( p_image->dat.semi_planar.y );
		p_image->dat.semi_planar.y = 0;
		p_image->dat.semi_planar.uv = 0;
	}
}

static void
AdapteImageFormat(unsigned char* p, morpho_ImageData *p_image, const char *p_format)
{
	int size_y = morpho_getImageSizeY( p_image->width, p_image->height, p_format );
	int size_u = morpho_getImageSizeU( p_image->width, p_image->height, p_format );
	int size_v = morpho_getImageSizeV( p_image->width, p_image->height, p_format );
	int size_uv = morpho_getImageSizeUV( p_image->width, p_image->height, p_format );
	int size_all = morpho_getImageSize( p_image->width, p_image->height, p_format );
    
	if( size_y > 0 )
	{
		if( size_u > 0 )//420p
		{
			p_image->dat.planar.y = p;
			p_image->dat.planar.u = ( char * )p_image->dat.planar.y + size_y;  // reference
			p_image->dat.planar.v = ( char * )p_image->dat.planar.u + size_u;  // reference
		}
		else if( size_uv > 0 )//420sp
		{
			p_image->dat.semi_planar.y = p;
			p_image->dat.semi_planar.uv = ( char * )p_image->dat.semi_planar.y + size_y;
		}
	}
	else
	{
		p_image->dat.p = p;
	}
}

int setEffectParamBacklight(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringBacklightParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("BacklightParam def: %d %d\r\n", param.gain, param.gaussian);

//    param.gain = 1;
//    param.gaussian = 1;

    if (input_param[0] != -1000) param.gain = input_param[0];
    if (input_param[1] != -1000) param.gaussian = input_param[1];

    PRINT_LOG("BacklightParam chg: %d %d\r\n", param.gain, param.gaussian);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}


int setEffectParamHighcontrast(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringHighcontrastParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("HighcontrastParam def: %d %d\r\n", param.strength, param.darkedge);

//    param.strength = 1;
//    param.darkedge = 1;

    if (input_param[0] != -1000) param.strength = input_param[0];
    if (input_param[1] != -1000) param.darkedge = input_param[1];

    PRINT_LOG("HighcontrastParam chg: %d %d\r\n", param.strength, param.darkedge);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamLighten(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringLightenParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("LightenParam def: %d \r\n", param.strength);

//    param.strength = 1;

    if (input_param[0] != -1000) param.strength = input_param[0];

    PRINT_LOG("LightenParam chg: %d \r\n", param.strength);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamMoza(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringMozaParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("MozaParam def: %d \r\n", param.moza_mode);

//    param.moza_mode = 1;

    if (input_param[0] != -1000) param.moza_mode = input_param[0];

    PRINT_LOG("MozaParam chg: %d \r\n", param.moza_mode);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamPartcolor(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringPartcolorParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("PartcolorParam def: %d %d\r\n", param.area, param.brightness);

//    param.area = 1;
//    param.brightness = 1;

    if (input_param[0] != -1000) param.area = input_param[0];
    if (input_param[1] != -1000) param.brightness = input_param[1];

    PRINT_LOG("PartcolorParam chg: %d %d\r\n", param.area, param.brightness);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}


int setEffectParamPoster(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringPosterParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("PosterParam def: %d %d %d %d\r\n", param.strength, param.vividness, param.box, param.boxSmall);

//    param.strength = 1;
//    param.vividness = 1;
//    param.box = 1;
//    param.boxSmall = 1;

    if (input_param[0] != -1000) param.strength = input_param[0];
    if (input_param[1] != -1000) param.vividness = input_param[1];
    if (input_param[2] != -1000) param.box = input_param[2];
    if (input_param[3] != -1000) param.boxSmall = input_param[3];

    PRINT_LOG("PosterParam chg: %d %d %d %d\r\n", param.strength, param.vividness, param.box, param.boxSmall);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamPretty(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringPrettyParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("PrettyParam def: %d %d %d %d %d %d %d %d %d %d %d %d\r\n", param.ideal_r, param.ideal_g , param.ideal_b, param.strength,
                                                        param.face_smallness, param.eye_vividness, param.eye_wideness, param.eye_sharpness,
                                                        param.eyelash_mode, param.red_eye, param.use_external_rect, param.rect_num);


#if 0
    param.ideal_r        = 255;
    param.ideal_g        = 240;
    param.ideal_b        = 209;
    param.strength       = 221;
    param.face_smallness = 173;
    param.eye_vividness  = 128;
    param.eye_wideness   = 128;
    param.eye_sharpness  = 128;
    param.eyelash_mode   = 1;
    param.red_eye        = 0;
#else
    param.ideal_r        = 255;
    param.ideal_g        = 240;
    param.ideal_b        = 209;
    param.strength       = 221;
    param.face_smallness = 0;
    param.eye_vividness  = 0;
    param.eye_wideness   = 0;
    param.eye_sharpness  = 0;
    param.eyelash_mode   = 0;
    param.red_eye        = 0;
#endif

//#if 0
    param.use_external_rect = 0;
    param.rect_num = 1;
    
    param.face_rects[0].sx = 500;
    param.face_rects[0].sy = 371;
    param.face_rects[0].ex = 664;
    param.face_rects[0].ey = 548;
    
//#endif
    
    
    PRINT_LOG("PrettyParam chg: %d %d %d %d %d %d %d %d %d %d %d %d\r\n", param.ideal_r, param.ideal_g , param.ideal_b, param.strength,
                                                        param.face_smallness, param.eye_vividness, param.eye_wideness, param.eye_sharpness,
                                                        param.eyelash_mode, param.red_eye, param.use_external_rect, param.rect_num);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}


int setEffectParamPretty2(morpho_EffectEngine* p_effect_engine, PARM_EFFECT  *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringPrettyParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("PrettyParam def: %d %d %d %d %d %d %d %d %d %d %d %d\r\n", param.ideal_r, param.ideal_g , param.ideal_b, param.strength,
                                                        param.face_smallness, param.eye_vividness, param.eye_wideness, param.eye_sharpness,
                                                        param.eyelash_mode, param.red_eye, param.use_external_rect, param.rect_num);


#if 0
    param.ideal_r        = 255;
    param.ideal_g        = 240;
    param.ideal_b        = 209;
    param.strength       = 221;
    param.face_smallness = 173;
    param.eye_vividness  = 128;
    param.eye_wideness   = 128;
    param.eye_sharpness  = 128;
    param.eyelash_mode   = 1;
    param.red_eye        = 0;
#else
    param.ideal_r        = input_param->ideal_r;
    param.ideal_g        = input_param->ideal_g;
    param.ideal_b        = input_param->ideal_b;
    param.strength       = input_param->strength;
    param.face_smallness = input_param->face_smallness;
    param.eye_vividness  = input_param->eye_vividness;
    param.eye_wideness   = input_param->eye_wideness;
    param.eye_sharpness  = input_param->eye_sharpness;
    param.eyelash_mode   = input_param->eyelash_mode;
    param.red_eye        = input_param->red_eye;
#endif

//#if 0
    param.use_external_rect = 0;
    param.rect_num = 1;
    
    param.face_rects[0].sx = 500;
    param.face_rects[0].sy = 371;
    param.face_rects[0].ex = 664;
    param.face_rects[0].ey = 548;
    
//#endif
    
    
    PRINT_LOG("PrettyParam chg: %d %d %d %d %d %d %d %d %d %d %d %d\r\n", param.ideal_r, param.ideal_g , param.ideal_b, param.strength,
                                                        param.face_smallness, param.eye_vividness, param.eye_wideness, param.eye_sharpness,
                                                        param.eyelash_mode, param.red_eye, param.use_external_rect, param.rect_num);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}



int setEffectParamRelic(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringRelicParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("RelicParam def: %d %d %d %d %d %d %d\r\n", param.amountBloom, param.useFrame, param.useGaussian, param.useColorShift,
                                        param.amountCornerBurn, param.amountVerticalStripes, param.amountFrameDust);

//    param.amountBloom           =  0;
//    param.useFrame              =  1;
//    param.useGaussian           =  1;
//    param.useColorShift         =  1;
//    param.amountCornerBurn      = 48;
//    param.amountVerticalStripes = 50;
//    param.amountFrameDust       = 13;

    PRINT_LOG("RelicParam chg: %d %d %d %d %d %d %d\r\n", param.amountBloom, param.useFrame, param.useGaussian, param.useColorShift,
                                        param.amountCornerBurn, param.amountVerticalStripes, param.amountFrameDust);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamMona(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringMonaParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("MonaParam def: %d %d\r\n", param.use_external_rect, param.rect_num);

#if 0
    param.use_external_rect = 1;
    param.rect_num = 1;
    
    /* for nekomusume in kawaharaas.jpg  */
    param.face_rects[0].sx = 154;
    param.face_rects[0].sy = 402;
    param.face_rects[0].ex = 384;
    param.face_rects[0].ey = 677;
    param.angles[0] = MORPHO_EFFECT_ENGINE_INCLINATION_0;
#endif
    
    
    PRINT_LOG("MonaParam chg: %d %d\r\n", param.use_external_rect, param.rect_num);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamBalloon(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringBalloonParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("BalloonParam def: %d %d\r\n", param.use_external_rect, param.rect_num);

#if 0
    param.use_external_rect = 1;
    param.rect_num = 1;
    
    /* for nekomusume in kawaharaas.jpg  */
    param.face_rects[0].sx = 154;
    param.face_rects[0].sy = 402;
    param.face_rects[0].ex = 384;
    param.face_rects[0].ey = 677;
    param.angles[0] = MORPHO_EFFECT_ENGINE_INCLINATION_0;
#endif
    
    
    PRINT_LOG("BalloonParam chg: %d %d\r\n", param.use_external_rect, param.rect_num);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamTwinkle(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringTwinkleParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("TwinkleParam def: %d\r\n", param.strength);

//    param.strength = 256;

    if (input_param[0] != -1000) param.strength = input_param[0];

    PRINT_LOG("TwinkleParam chg: %d\r\n", param.strength);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamColorfilter(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringColorFilterParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("ColorfilterParam def red: %d\r\n", param.red);
    PRINT_LOG("ColorfilterParam def green: %d\r\n", param.green);
    PRINT_LOG("ColorfilterParam def blue: %d\r\n", param.blue);

//    param.red = 256;
//    param.green = 256;
//    param.blue = 128;

    if (input_param[0] != -1000) param.red = input_param[0];
    if (input_param[1] != -1000) param.green = input_param[1];
    if (input_param[2] != -1000) param.blue = input_param[2];
   
    PRINT_LOG("ColorfilterParam chg red: %d\r\n", param.red);
    PRINT_LOG("ColorfilterParam chg green: %d\r\n", param.green);
    PRINT_LOG("ColorfilterParam chg blue: %d\r\n", param.blue);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamNostalgy(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringNostalgyParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("NostalgyParam def radius: %d\r\n", param.radius);
    PRINT_LOG("NostalgyParam def tone_curve_strength: %d\r\n", param.tone_curve_strength);
    PRINT_LOG("NostalgyParam def tone_map_strength: %d\r\n", param.tone_map_strength);
	PRINT_LOG("NostalgyParam def cross_processing_mode: %d\r\n", param.cross_processing_mode);

//    param.radius = 999;
//    param.tone_curve_strength = 256;
//    param.tone_map_strength = 256;
//    param.cross_processing_mode = MORPHO_EFFECT_FILTERING_NOSTALGY_CROSSPROCESSING_BLUE;

    if (input_param[0] != -1000) param.radius = input_param[0];
    if (input_param[1] != -1000) param.tone_curve_strength = input_param[1];
    if (input_param[2] != -1000) param.tone_map_strength = input_param[2];
    if (input_param[3] != -1000) param.cross_processing_mode = input_param[3];
   
    PRINT_LOG("NostalgyParam chg radius: %d\r\n", param.radius);
    PRINT_LOG("NostalgyParam chg tone_curve_strength: %d\r\n", param.tone_curve_strength);
    PRINT_LOG("NostalgyParam chg tone_map_strength: %d\r\n", param.tone_map_strength);
	PRINT_LOG("NostalgyParam def cross_processing_mode: %d\r\n", param.cross_processing_mode);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamSelectcolor(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringSelectColorParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("SelectColorParam def red: %d\r\n", param.red);
    PRINT_LOG("SelectColorParam def green: %d\r\n", param.green);
    PRINT_LOG("SelectColorParam def blue: %d\r\n", param.blue);
    PRINT_LOG("SelectColorParam def range: %d\r\n", param.range);
    PRINT_LOG("SelectColorParam def brightness: %d\r\n", param.brightness);


//    param.red = 128;           //(0-255)
//    param.green = 128;        //(0-255)
//    param.blue = 0;         //(0-255)
//    param.range = 50;         //(0-1024)
//    param.brightness = 384;   //(0:îíçï - 256:êFã≠í≤Ç»Çµ - 1024)

    if (input_param[0] != -1000) param.red = input_param[0];
    if (input_param[1] != -1000) param.green = input_param[1];
    if (input_param[2] != -1000) param.blue = input_param[2];
    if (input_param[3] != -1000) param.range = input_param[3];
    if (input_param[4] != -1000) param.brightness = input_param[4];
   
    PRINT_LOG("SelectColorParam chg red: %d\r\n", param.red);
    PRINT_LOG("SelectColorParam chg green: %d\r\n", param.green);
    PRINT_LOG("SelectColorParam chg blue: %d\r\n", param.blue);
    PRINT_LOG("SelectColorParam chg range: %d\r\n", param.range);
    PRINT_LOG("SelectColorParam chg brightness: %d\r\n", param.brightness);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}


int setEffectParamKaleidoscope(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringKaleidoscopeParam param;
    
    ret = morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("KaleidoscopeParam def center_x: %d\r\n", param.center_x);
    PRINT_LOG("KaleidoscopeParam def center_y: %d\r\n", param.center_y);
    PRINT_LOG("KaleidoscopeParam def tri_radius: %d\r\n", param.tri_radius);
    PRINT_LOG("KaleidoscopeParam def angle: %d\r\n", param.angle);

//    param.center_x = 640;
//    param.center_y = 480;
//    param.tri_radius = 100;
//    param.angle = 0;

    if (input_param[0] != -1000) param.center_x = input_param[0];
    if (input_param[1] != -1000) param.center_y = input_param[1];
    if (input_param[2] != -1000) param.tri_radius = input_param[2];
    if (input_param[3] != -1000) param.angle = input_param[3];
   
    PRINT_LOG("KaleidoscopeParam chg center_x: %d\r\n", param.center_x);
    PRINT_LOG("KaleidoscopeParam chg center_y: %d\r\n", param.center_y);
    PRINT_LOG("KaleidoscopeParam chg tri_radius: %d\r\n", param.tri_radius);
    PRINT_LOG("KaleidoscopeParam chg angle: %d\r\n", param.angle);

    ret = morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamPencil(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringPencilParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("PencilParam def: %d %d\r\n", param.touch, param.saturation);

    if (input_param[0] != -1000) param.touch = input_param[0];
    if (input_param[1] != -1000) param.saturation= input_param[1];
    //if (input_param[1] != -1000) param.lineDensity= input_param[1];

    PRINT_LOG("PencilParam chg: %d %d\r\n", param.touch, param.saturation);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamFishEye1(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringFishEye1Param param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }


    PRINT_LOG("FishEye1Param def: def ratio:%d \n", param.deform_ratio);

//    param.deform_ratio = 100; 

    if (input_param[0] != -1000) param.deform_ratio = input_param[0];

    PRINT_LOG("FishEye1Param chg: def ratio:%d \n", param.deform_ratio);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}


int setEffectParamMirror(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringMirrorParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("Mirror def:  \n");

    PRINT_LOG("MirrorParam chg:  \n");

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamDeblur(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
	morpho_EffectFilteringDeblurParam param;

    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("DeblurParam def area: %d\r\n", param.area);

//    param.area = 32;

    if (input_param[0] != -1000) param.area = input_param[0];

    PRINT_LOG("DeblurParam chg area: %d\r\n", param.area);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamStarburst(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringStarburstParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("StarburstParam def: %d %d\r\n", param.strength, param.starcount);

    if (input_param[0] != -1000) param.strength = input_param[0];
    if (input_param[1] != -1000) param.starcount = input_param[1];

    PRINT_LOG("StarburstParam chg: %d %d\r\n", param.strength, param.starcount);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamOverexpose(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringOverexposeParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("OverexposeParam def: %d %d %d %d %d\r\n", param.thres, param.gain, param.blur_depth, param.blur_iters, param.blur_radius);

    if (input_param[0] != -1000) param.thres = input_param[0];
    if (input_param[1] != -1000) param.gain = input_param[1];
    if (input_param[2] != -1000) param.blur_depth = input_param[2];
    if (input_param[3] != -1000) param.blur_iters = input_param[3];
    if (input_param[4] != -1000) param.blur_radius = input_param[4];

    PRINT_LOG("OverexposeParam chg: %d %d %d %d %d\r\n", param.thres, param.gain, param.blur_depth, param.blur_iters, param.blur_radius);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamDefocus(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringDefocusParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("DefocusParam def: %d %d\r\n", param.strength, param.octagonal_lens);

    if (input_param[0] != -1000) param.strength = input_param[0];
    if (input_param[1] != -1000) param.octagonal_lens = input_param[1];

    PRINT_LOG("DefocusParam chg: %d %d\r\n", param.strength, param.octagonal_lens);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamMiniture(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringMiniatureParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("MiniatureParam def: %d %d %d %d\r\n", param.vertical_center, param.tilt_strength, param.window_size, param.saturation_boost);

    if (input_param[0] != -1000) param.vertical_center = input_param[0];
    if (input_param[1] != -1000) param.tilt_strength = input_param[1];
    if (input_param[2] != -1000) param.window_size = input_param[2];
    if (input_param[3] != -1000) param.saturation_boost = input_param[3];

    PRINT_LOG("MiniatureParam chg: %d %d %d %d\r\n", param.vertical_center, param.tilt_strength, param.window_size, param.saturation_boost);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamEdo(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringEdoParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("EdoParam def: %d\r\n", param.age);

    if (input_param[0] != -1000) param.age = input_param[0];

    PRINT_LOG("EdoParam chg: %d\r\n", param.age);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamComic(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringComicParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("ComicParam def: %d %d %d %d %d %d\r\n", param.gaussian, param.edge_kernel, param.edge_a, param.edge_b, param.intensy_a, param.thinning);

    if (input_param[0] != -1000) param.gaussian = input_param[0];
    if (input_param[1] != -1000) param.edge_kernel = input_param[1];
    if (input_param[2] != -1000) param.edge_a = input_param[2];
    if (input_param[3] != -1000) param.edge_b = input_param[3];
    if (input_param[4] != -1000) param.intensy_a = input_param[4];
    if (input_param[5] != -1000) param.thinning = input_param[5];

    PRINT_LOG("ComicParam chg: %d %d %d %d %d %d\r\n", param.gaussian, param.edge_kernel, param.edge_a, param.edge_b, param.intensy_a, param.thinning);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamVivid(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringVividParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("VividParam def: %d\r\n", param.strength);

    if (input_param[0] != -1000) param.strength = input_param[0];

    PRINT_LOG("VividParam chg: %d\r\n", param.strength);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int setEffectParamHarris(morpho_EffectEngine* p_effect_engine, int *input_param)
{
    int ret = MORPHO_OK;
    morpho_EffectFilteringHarrisParam param;
    
    ret |= morpho_EffectEngine_getEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "getEffectParam failed.\n" );
        return ret;
    }

    PRINT_LOG("HarrisParam def green_delay: %d\r\n", param.green_delay);
    PRINT_LOG("HarrisParam def blue_delay: %d\r\n", param.blue_delay);
    PRINT_LOG("HarrisParam def skip_frame_num: %d\r\n", param.skip_frame_num);

#if 1
    if (input_param[0] != -1000) param.green_delay = input_param[0];
    if (input_param[1] != -1000) param.blue_delay = input_param[1];
    if (input_param[2] != -1000) param.skip_frame_num = input_param[2];
#endif
   
    PRINT_LOG("HarrisParam chg green_delay: %d\r\n", param.green_delay);
    PRINT_LOG("HarrisParam chg blue_delay: %d\r\n", param.blue_delay);
    PRINT_LOG("HarrisParam chg skip_frame_num: %d\r\n", param.skip_frame_num);

    ret |= morpho_EffectEngine_setEffectParam( p_effect_engine, (void *)(&param));
    if( ret != MORPHO_OK ){
        PRINT_LOG( "setEffectParam failed.\n" );
        return ret;
    }
    
    return ret;
}

int Effect_Init(const char* effect_name, const char* format, int height, int width)
{
	int buffer_size;
	int ret = 0;

	p_effect_name = effect_name;
	p_format = format;
	input_image.width = width;
	input_image.height = height;
	output_image.width = width;
	output_image.height = height;

	PRINT_LOG( "%s\n", morpho_EffectEngine_getVersion() );
	buffer_size = morpho_EffectEngine_getBufferSize( p_effect_name, p_format,
	                                                 width, height, width, height,
	                                                 1, MORPHO_EFFECT_ENGINE_MEMORY_TYPE_NONE );
        PRINT_LOG( "ken.li the buff size is %d",  buffer_size);
        PRINT_LOG( "ken.li the buff size is %d",  buffer_size);
	if( buffer_size == 0 )
	{
		PRINT_LOG( "Error in morpho_EffectEngine_getBufferSize : Returned buffer size is zero.\n" );
		return -1;
	}
	p_buffer = malloc( buffer_size );
        PRINT_LOG( "ken.li the buff size is %d",  buffer_size);
	if( p_buffer == 0 )
	{
		PRINT_LOG( "Memory allocation error\n" );
		return -1;
	}

	PRINT_LOG( "Allocated buffer size: %d bytes\n", buffer_size );
	APICALL( morpho_EffectEngine_initialize( &effect_engine, p_effect_name, p_format,
	                                     p_buffer, buffer_size, width, height, width, height,
	                                     1, MORPHO_EFFECT_ENGINE_MEMORY_TYPE_NONE ),
	     "morpho_EffectEngine_initialize" );
	if( ret != MORPHO_OK ) goto L_destruct_buffer;

	allocateImageData( &output_image, p_format );
        int input_param[6] = {-1000,-1000,-1000,-1000,-1000,-1000};
	
#if 0//set parameter
	if(!strcmp(p_effect_name, "ES_BACKLIGHT")) {
		ret |= setEffectParamBacklight(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_HIGHCONTRAST")){
		ret |= setEffectParamHighcontrast(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_LIGHTEN")){
		ret |= setEffectParamLighten(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_MOZA")){
		ret |= setEffectParamMoza(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_PARTCOLOR")){
		ret |= setEffectParamPartcolor(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_POSTER")){
		ret |= setEffectParamPoster(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_PRETTY")){
		ret |= setEffectParamPretty(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "EM_RELIC")){
		ret |= setEffectParamRelic(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_MONA")){
		ret |= setEffectParamMona(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_BALLOON")){
		ret |= setEffectParamBalloon(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "EM_TWINKLE")){
		ret |= setEffectParamTwinkle(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_COLORFILTER")){
		ret |= setEffectParamColorfilter(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_NOSTALGY")){
		ret |= setEffectParamNostalgy(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_SELECTCOLOR")){
		ret |= setEffectParamSelectcolor(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_KALEIDOSCOPE")){
		ret |= setEffectParamKaleidoscope(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_PENCIL")){
		ret |= setEffectParamPencil(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_FISHEYE1")){
		ret |= setEffectParamFishEye1(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_MIRROR")){
		ret |= setEffectParamMirror(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_PINFOCUS")){
		ret |= setEffectParamDeblur(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_STARBURST")){
		ret |= setEffectParamStarburst(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_EDO")){
		ret |= setEffectParamEdo(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_COMIC")){
		ret |= setEffectParamComic(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_DEFOCUS")){
		ret |= setEffectParamDefocus(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_OVEREXPOSE")){
		ret |= setEffectParamOverexpose(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_VIVID")){
		ret |= setEffectParamVivid(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "ES_MINIATURE")){
		ret |= setEffectParamMiniture(&effect_engine, &input_param[0]);
	} else if(!strcmp(p_effect_name, "EM_HARRIS")){
		ret |= setEffectParamHarris( &effect_engine, &input_param[0] );
	}
	if( ret != MORPHO_OK )
	{
		PRINT_LOG( "Parameter setting error.\n" );
		goto L_destruct_buffer;
	}
#endif

if(!strcmp(p_effect_name, "ES_PRETTY")){

		ret |= setEffectParamPretty(&effect_engine, &input_param[0]);
	}
if(!strcmp(p_effect_name, "ES_OVEREXPOSE")){
		ret |= setEffectParamOverexpose(&effect_engine, &input_param[0]);

	}
if( ret != MORPHO_OK )
	{
		PRINT_LOG( "Parameter setting error.\n" );

		goto L_destruct_buffer;
	}

	return ret;
L_destruct_buffer:
	if(p_buffer)
	{
		free( p_buffer );
		p_buffer = NULL;
	}

	return -1;
}

int Effect_Function(unsigned char *src, const char *filename, PARM_EFFECT *input_param)
{
	int ret = 0;

	PRINT_LOG( "\nMorpho Effect Library makes effect using %s\n", p_effect_name );


	setEffectParamPretty2(&effect_engine, input_param);
	
	AdapteImageFormat(src , &input_image , p_format);

	int ids[2];
	int granu;
	int progress = 0;
	int hasError = 0;

	morpho_RectInt rect;
	morpho_RectInt_setRect( &rect, 0, 0, output_image.width, output_image.height );
        
	APICALL( morpho_EffectEngine_registerImage( &effect_engine, &input_image, &ids[0] ), "morpho_EffectEngine_registerImage" );
	APICALL( morpho_EffectEngine_start( &effect_engine, ids, 1, &output_image, &rect, 32768 ), "morpho_EffectEngine_start" );

	APICALL( morpho_EffectEngine_getProgressGranu( &effect_engine, &granu ), "morpho_EffectEngine_getProgressGranu" );
	progress = granu;
	while( progress <= 32768 )
	{
		ret = morpho_EffectEngine_run( &effect_engine, progress );
		if( ret != MORPHO_OK && ret != MORPHO_DOPROCESS )
		{
			PRINT_LOG( "Error in morpho_EffectEngine_run. retcode=%08X\n", ret );
			hasError = ret;
			break;
		}
		progress += granu;
	}
        
	APICALL( morpho_EffectEngine_stop( &effect_engine ), "morpho_EffectEngine_stop" );
	APICALL( morpho_EffectEngine_releaseImage( &effect_engine, ids[0] ), "morpho_EffectEngine_releaseImage" );

	if( !hasError )
	{
		if(filename)
		{
			//morpho_write_jpeg( &output_image, filename, p_format );
		}
		else
		{
			PRINT_LOG("start memcpy");
			int size = output_image.height * output_image.width;
			if (!strcmp(p_format, "YUV420_SEMIPLANAR"))
			{
				memcpy(src, output_image.dat.semi_planar.y, size);
				memcpy(src+size, output_image.dat.semi_planar.uv, (size/2));
			}
			else if (!strcmp(p_format, "YUV420_PLANAR"))
			{
				memcpy(src, output_image.dat.planar.y, size);
				memcpy(src+size, output_image.dat.planar.u, (size/4));  // reference
				memcpy(src+size+size/4, output_image.dat.planar.v, (size/4));  //reference
			}
			else if (!strcmp(p_format, "YUV422_UYVY"))
			{
				memcpy(src, output_image.dat.p, (size*2));
			}
			PRINT_LOG("end memcpy");
		}
	}

	PRINT_LOG( "Done.\n" );

	return ret;
}

int Effect_Finalize()
{
	int ret = 0;
	
	if(!effect_engine.p)
		return ret;
	
	APICALL( morpho_EffectEngine_finalize( &effect_engine ), "morpho_EffectEngine_finalize" );
	effect_engine.p = NULL;
	freeImageData( &output_image );
	if(p_buffer)
	{
		free( p_buffer );
		p_buffer = NULL;
	}

	return ret;
}

