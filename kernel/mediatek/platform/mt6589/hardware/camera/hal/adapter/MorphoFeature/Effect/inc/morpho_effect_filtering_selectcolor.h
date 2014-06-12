/**
 * @file    morpho_effect_filtering_selectcolor.h
 * @brief   Morpho Filtering Effect "SELECTCOLOR" module.
 *
 * effect_name     ...  "ES_SELECTCOLOR"
 * needs_image_num ...  1
 *
 * Copyright (C) 2011 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_SELECTCOLOR_H
#define MORPHO_EFFECT_FILTERING_SELECTCOLOR_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * EM_SELECTCOLOR エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int red;              /**< 選択した色（赤成分）(0-255) default:200 */
    int green;            /**< 選択した色（緑成分）(0-255) default:20 */
    int blue;             /**< 選択した色（青成分）(0-255) default:20 */
    int range;            /**< 選択する色の範囲（0-1024）default:12 */
    int brightness;       /**< 色強調(0:白黒 - 256:色強調なし - 1024) default:384 */
} morpho_EffectFilteringSelectColorParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_SELECTCOLOR_H */
