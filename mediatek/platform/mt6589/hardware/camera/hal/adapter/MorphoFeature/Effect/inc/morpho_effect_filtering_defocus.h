/**
 * @file    morpho_effect_filtering_defocus.h
 * @brief   Morpho Filtering Effect "DEFOCUS" module.
 *
 * effect_name     ...  "ES_DEFOCUS"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_DEFOCUS_H
#define MORPHO_EFFECT_FILTERING_DEFOCUS_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * ES_DEFOCUS エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int strength;		/* DEFOCUS強度(0～256) default:128 */
    int octagonal_lens;	/* 八角形のレンズ(使/無し) default:0 */
} morpho_EffectFilteringDefocusParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_DEFOCUS_H */
