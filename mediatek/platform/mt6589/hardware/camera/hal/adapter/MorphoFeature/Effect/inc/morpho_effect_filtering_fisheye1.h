/**
 * @file    morpho_effect_filtering_fisheye1.h
 * @brief   Morpho Filtering Effect "FISHEYE1" module.
 *
 * effect_name     ...  "ES_FISHEYE1"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_FISHEYE1_H
#define MORPHO_EFFECT_FILTERING_FISHEYE1_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * EM_FISHEYE1 エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int deform_ratio;
} morpho_EffectFilteringFishEye1Param;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_FISHEYE1_H */
