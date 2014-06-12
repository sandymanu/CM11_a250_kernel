/**
 * @file    morpho_effect_filtering_glass.h
 * @brief   Morpho Filtering Effect "GLASS" module.
 *
 * effect_name     ...  "ES_GLASS"
 * needs_image_num ...  1
 *
 * Copyright (C) 2010 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_GLASS_H
#define MORPHO_EFFECT_FILTERING_GLASS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ES_GLASS エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int amlitude;   //ガラス歪みレベル 5 ~ 40 : default 20
    int blocksize;  //ガラス格子のサイズ　10 ~ 200 : default 80
} morpho_EffectFilteringGlassParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_GLASS_H */
