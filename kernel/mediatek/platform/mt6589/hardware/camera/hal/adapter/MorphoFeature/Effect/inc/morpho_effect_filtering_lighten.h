/**
 * @file    morpho_effect_filtering_lightent.h
 * @brief   Morpho Filtering Effect "LIGHTEN" module.
 *
 * effect_name     ...  "ES_LIGHTEN"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_LIGHTEN_H
#define MORPHO_EFFECT_FILTERING_LIGHTEN_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * ES_LIGHTEN エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int strength;   /* LIGHTEN強度(0～256) default:64 */
} morpho_EffectFilteringLightenParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_LIGHTEN_H */
