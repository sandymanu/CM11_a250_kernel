/**
 * @file    morpho_effect_filtering_colorfilter.h
 * @brief   Morpho Filtering Effect "COLORFILTER" module.
 *
 * effect_name     ...  "ES_COLORFILTER"
 * needs_image_num ...  1
 *
 * Copyright (C) 2011 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_COLORFILTER_H
#define MORPHO_EFFECT_FILTERING_COLORFILTER_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * EM_COLORFILTER エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int red;              /**< 赤成分の強さ(0-256) default:128 */
    int green;            /**< 緑成分の強さ(0-256) default:256 */
    int blue;             /**< 青成分の強さ(0-256) default:128 */
} morpho_EffectFilteringColorFilterParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_COLORFILTER_H */
