/**
 * @file    morpho_effect_filtering_water.h
 * @brief   Morpho Filtering Effect "WATER" module.
 *
 * effect_name     ...  "ES_WATER"
 * needs_image_num ...  1
 *
 * Copyright (C) 2010 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_WATER_H
#define MORPHO_EFFECT_FILTERING_WATER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ES_WATER エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int source_x;      //波源の中心x  0~width-1
    int source_y;      //波源の中心y  0~height-1
    int source_size;   //波源の半径   1~30
    int source_power; //波源のパワー  1~120
} morpho_EffectFilteringWaterParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_WATER_H */
