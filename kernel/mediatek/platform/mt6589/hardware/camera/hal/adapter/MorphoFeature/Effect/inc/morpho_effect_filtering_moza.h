/**
 * @file    morpho_effect_filtering_moza.h
 * @brief   Morpho Filtering Effect "Moza" module.
 *
 * effect_name     ...  "ES_MOZA"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_MOZA_H
#define MORPHO_EFFECT_FILTERING_MOZA_H

#ifdef __cplusplus
extern "C" {
#endif

#define MORPHO_EFFECT_FILTERLING_MOZA_RECT_NUM 10
    
/**  
 * ES_MOZA エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int moza_mode;   /* 0..only_eyes  1..all_face  2..rects */
    int rect_num;    /* 指定rect数 moza_mode=2のとき有効 */
    morpho_RectInt rects[MORPHO_EFFECT_FILTERLING_MOZA_RECT_NUM];  /* moza_mode=2のとき有効 */
} morpho_EffectFilteringMozaParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_MOZA_H */
