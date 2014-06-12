/**
 * @file    morpho_effect_filtering_kaleidoscope.h
 * @brief   Morpho Filtering Effect "KALEIDOSCOPE" module.
 *
 * effect_name     ...  "ES_KALEIDOSCOPE"
 * needs_image_num ...  1
 *
 * Copyright (C) 2011 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_KALEIDOSCOPE_H
#define MORPHO_EFFECT_FILTERING_KALEIDOSCOPE_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * EM_COLORFILTER エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int center_x;           /**< 中心X座標 default:画像中央部X座標 */
    int center_y;           /**< 中心Y座標 default:画像中央部Y座標 */
    int tri_radius;         /**< 三角形の外心の半径 default:160 */
    int angle;              /**< 三角形の角度(0-360)  default:0*/
    int orientation;        /**< 画像の向き(0-3) default:0*/
} morpho_EffectFilteringKaleidoscopeParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_KALEIDOSCOPE_H */
