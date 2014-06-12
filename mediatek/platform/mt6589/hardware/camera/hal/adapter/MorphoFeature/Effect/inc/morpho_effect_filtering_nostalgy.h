/**
 * @file    morpho_effect_filtering_nostalgy.h
 * @brief   Morpho Filtering Effect "NOSTALGY" module.
 *
 * effect_name     ...  "ES_NOSTALGY"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_NOSTALGY_H
#define MORPHO_EFFECT_FILTERING_NOSTALGY_H

#ifdef __cplusplus
extern "C" {
#endif

enum {
    MORPHO_EFFECT_FILTERING_NOSTALGY_CROSSPROCESSING_YELLOW = 0,
    MORPHO_EFFECT_FILTERING_NOSTALGY_CROSSPROCESSING_BLUE,
    MORPHO_EFFECT_FILTERING_NOSTALGY_CROSSPROCESSING_NUM,
};

/**  
 * EM_NOSTALGY エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int radius;                   /**< 暗くする半径（0%-1000%) 
                                       対角線に対するパーセンテージ） */
    int tone_curve_strength;      /**< ガンマ補正の強さ(0-256) */
    int tone_map_strength;        /**< 色補正の強さ(0-256) */
    int cross_processing_mode;    /**< クロスプロセスのモード*/
} morpho_EffectFilteringNostalgyParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_NOSTALGY_H */
