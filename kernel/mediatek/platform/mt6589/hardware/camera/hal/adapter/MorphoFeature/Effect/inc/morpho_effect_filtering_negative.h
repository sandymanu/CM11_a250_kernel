/**
 * @file    morpho_effect_filtering_negative.h
 * @brief   Morpho Filtering Effect "NEGATIVE" module.
 *
 * effect_name     ...  "ES_NEGATIVE"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_NEGATIVE_H
#define MORPHO_EFFECT_FILTERING_NEGATIVE_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * ES_NEGATIVE エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int reverse_red;   /* RGBのR反転 default:1 */
    int reverse_green;   /* RGBのG反転 default:1 */
    int reverse_blue;   /* RGBのBの反転 default:1 */
} morpho_EffectFilteringNegativeParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_NEGATIVE_H */
