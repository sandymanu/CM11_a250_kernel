/**
 * @file    morpho_effect_filtering_warm.h
 * @brief   Morpho Filtering Effect "WARM" module.
 *
 * effect_name     ...  "ES_WARM"
 * needs_image_num ...  1
 *
 * Copyright (C) 2010 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_WARM_H
#define MORPHO_EFFECT_FILTERING_WARM_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ES_WARM エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int green_high;   /* Greenの上限 170~255 : default 215 */
    int blue_low;     /* Blueの下限 0~128 : default 80 */
    int blue_high;    /* Blueの上限 blue_low~255  : default 215 */
} morpho_EffectFilteringWarmParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_WARM_H */
