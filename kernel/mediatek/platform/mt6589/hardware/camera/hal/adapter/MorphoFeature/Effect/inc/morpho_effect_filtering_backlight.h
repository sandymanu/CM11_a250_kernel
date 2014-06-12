/**
 * @file    morpho_effect_filtering_backlight.h
 * @brief   Morpho Filtering Effect "Backlight" module.
 *
 * effect_name     ...  "ES_BACKLIGHT"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_BACKLIGHT_H
#define MORPHO_EFFECT_FILTERING_BACKLIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * ES_BACKLIGHT エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int gain;     /* ゲインアップレベル(0～256) 256が最高 デフォルトは64 */
    int gaussian; /* ガウシアン関数を使用するかどうか。 0…使用しない。 1…使用する。 デフォルト:1 */
} morpho_EffectFilteringBacklightParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_BACKLIGHT_H */
