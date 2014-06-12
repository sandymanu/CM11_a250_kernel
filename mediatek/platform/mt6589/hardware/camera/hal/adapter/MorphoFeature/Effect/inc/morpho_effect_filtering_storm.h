/**
 * @file    morpho_effect_filtering_storm.h
 * @brief   Morpho Filtering Effect "STORM" module.
 *
 * effect_name     ...  "ES_STORM"
 * needs_image_num ...  1
 *
 * Copyright (C) 2010 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_STORM_H
#define MORPHO_EFFECT_FILTERING_STORM_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ES_STORM エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int rain_angle;     //雨の角度　-30 ~ 30 : default 10
    int rain_strength;  //雨の強度　0 ~ 10 : default 10
    int rain_brightness;//雨の線の色　50 ~ 200 : default 130
    int rain_speed;     //雨のスピード1 ~ 100 : default 30
    int lightning_enable; // 雷mode   0 ~ 1 : default 1
    int lightning_num;    // 雷の数　0 ~ 10 : default 1
} morpho_EffectFilteringStormParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_STORM_H */
