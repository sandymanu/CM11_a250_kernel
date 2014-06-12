/**
 * @file    morpho_effect_filtering_poster.h
 * @brief   Morpho Filtering Effect "Poster" module.
 *
 * effect_name     ...  "ES_POSTER"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_POSTER_H
#define MORPHO_EFFECT_FILTERING_POSTER_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * ES_POSTER エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int strength;         /* 強調係数  0～256 */
    int vividness;        /* 鮮やかさ(0-256) */
    int box;              /* 絵画っぽさ(0-256) */
    int boxSmall;         /* 将来拡張予定(0-256) */
} morpho_EffectFilteringPosterParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_POSTER_H */
