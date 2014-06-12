/**
 * @file    morpho_effect_filtering_wave.h
 * @brief   Morpho Filtering Effect "WAVE" module.
 *
 * effect_name     ...  "ES_WAVE"
 * needs_image_num ...  1
 *
 * Copyright (C) 2010 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_WAVE_H
#define MORPHO_EFFECT_FILTERING_WAVE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ES_WAVE エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int orientation;  //方向 0: bottom
                      //      1: left
                      //      2: up
                      //      3: right
    int water_percent;  //波部分は画面全体のパーセンテージ 1 ~ 50 : default 35
    int wave_period;    //波の周期 5 ~ 100(frame) : default 30
    int wave_amplitude; //波の振幅 1 ~ 20: default 15
    int wave_length;    //最大の波長  1 ~ 20: default 5
} morpho_EffectFilteringWaveParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_WAVE_H */
