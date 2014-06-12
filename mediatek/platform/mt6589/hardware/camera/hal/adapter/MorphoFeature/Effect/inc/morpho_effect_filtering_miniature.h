/**
 * @file    morpho_effect_filtering_highcontrast.h
 * @brief   Morpho Filtering Effect "MINIATURE" module.
 *
 * effect_name     ...  "ES_MINIATURE"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_MINIATURE_H
#define MORPHO_EFFECT_FILTERING_MINIATURE_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * ES_MINIATURE エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int vertical_center;   /* ウインドウ(効果をかける範囲)の中央(0～256) 0…一番上が中心 256…一番下が中心 default:128 */
    int tilt_strength;     /* 被写体深度(0～256) default:128 */
    int window_size;       /* ウインドウ(効果をかける範囲)の垂直方向のサイズ(0～256) default:128 */
    int saturation_boost;		/* 原色加工強度係数(0～256) default:128 */
} morpho_EffectFilteringMiniatureParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_MINIATURE_H */
