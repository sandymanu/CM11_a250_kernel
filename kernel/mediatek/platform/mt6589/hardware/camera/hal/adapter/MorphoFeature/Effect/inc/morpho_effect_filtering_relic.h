/**
 * @file    morpho_effect_filtering_relic.h
 * @brief   Morpho Filtering Effect "Relic" module.
 *
 * effect_name     ...  "EM_RELIC"
 * needs_image_num ...  1
 *
 * @author Ola Nordqvist (n-ola@morphoinc.com)
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_RELIC_H
#define MORPHO_EFFECT_FILTERING_RELIC_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * EM_RELIC エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    unsigned char amountBloom;				/* 0～255   「デフォルト：０」*/

    unsigned char useFrame;					/* 使/無し	「デフォルト：使」*/
    unsigned char useGaussian;				/* 使/無し	「デフォルト：使」（注意: 本当に使わなかったら */
    
	unsigned char useColorShift;			/* 使/無し	「デフォルト：使」*/

	unsigned char amountCornerBurn;			/* 0～255	「デフォルト：２２０」*/

	unsigned char amountVerticalStripes;	/* 0～255	「デフォルト：５０」*/

	unsigned char amountFrameDust;			/* 0～255	「デフォルト：１３」*/
    
} morpho_EffectFilteringRelicParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_RELIC_H */
