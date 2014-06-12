/**
 * @file    morpho_effect_filtering_partcolor.h
 * @brief   Morpho Filtering Effect "Partcolor" module.
 *
 * effect_name     ...  "ES_PARTCOLOR"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_PARTCOLOR_H
#define MORPHO_EFFECT_FILTERING_PARTCOLOR_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * ES_PARTCOLOR エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int area;        /* 全体のどれだけの面積に色をつけるか(0-256) */
    int brightness;  /* 鮮やかさ(0-256) */
} morpho_EffectFilteringPartcolorParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_PARTCOLOR_H */
