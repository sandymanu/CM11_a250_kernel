/**
 * @file    morpho_effect_animation_zoom.h
 * @brief   Morpho Animation Effect "ZOOM" module.
 *
 * effect_name     ...  "AN_ZOOM"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_ANIMATION_ZOOM_H
#define MORPHO_EFFECT_ANIMATION_ZOOM_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * AN_ZOOM エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    morpho_RectInt startRect;
    morpho_RectInt endRect;
    int color_r; /**< 背景色(r成分) */
    int color_g; /**< 背景色(g成分) */
    int color_b; /**< 背景色(b成分) */
    const morpho_ImageData* p_bg_image;  /**< 背景画像. */
    int draw_all_bg; /**<背景色、背景画像を出力画像全体に描画するかどうか 0…塗りつぶさない 1…指定rectのみ 2…出力画像全体 */
} morpho_EffectAnimationZoomParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_ANIMATION_ZOOM_H */
