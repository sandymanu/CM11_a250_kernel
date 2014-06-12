/**
 * @file    morpho_effect_filtering_overexpose.h
 * @brief   Morpho Filtering Effect "OVEREXPOSE" module.
 *
 * effect_name     ...  "ES_OVEREXPOSE"
 * needs_image_num ...  1
 *
 * Copyright (C) 2010 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_OVEREXPOSE_H
#define MORPHO_EFFECT_FILTERING_OVEREXPOSE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ES_OVEREXPOSE エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int thres;
    int gain;
    int blur_depth;
    int blur_iters;
    int blur_radius;
} morpho_EffectFilteringOverexposeParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_OVEREXPOSE_H */
