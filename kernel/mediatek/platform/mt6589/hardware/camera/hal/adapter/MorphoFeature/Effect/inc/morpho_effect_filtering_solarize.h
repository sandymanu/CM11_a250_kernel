/**
 * @file    morpho_effect_filtering_solarize.h
 * @brief   Morpho Filtering Effect "SOLARIZE" module.
 *
 * effect_name     ...  "ES_SOLARIZE"
 * needs_image_num ...  1
 *
 * Copyright (C) 2010 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_SOLARIZE_H
#define MORPHO_EFFECT_FILTERING_SOLARIZE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ES_SOLARIZE エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int thres;          //露出最大値、thresを超えると色反転する　1~255 default:140
    int normalization;  //正規化 1:する 0:しない default:1
} morpho_EffectFilteringSolarizeParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_SOLARIZE_H */
