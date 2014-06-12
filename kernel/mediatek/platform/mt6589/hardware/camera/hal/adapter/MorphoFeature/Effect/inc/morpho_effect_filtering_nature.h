/**
 * @file    morpho_effect_filtering_nature.h
 * @brief   Morpho Filtering Effect "NATURE" module.
 *
 * effect_name     ...  "ES_NATURE"
 * needs_image_num ...  1
 *
 * Copyright (C) 2010 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_NATURE_H
#define MORPHO_EFFECT_FILTERING_NATURE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ES_NATURE エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int contrast;     /* コントラスト 0~127 : default 35*/
    int brightness;   /* 明度 0~127 : default 10*/
    int shadow;       /* シャドーの強さ -128~128  : default 30 正数:暗い、負数:明るい*/
    int radius_in;    /* 内径 0~100  : default 55*/
    int radius_out;   /* 外径 radius_in ~ 100 : default 75*/
} morpho_EffectFilteringNatureParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_NATURE_H */
