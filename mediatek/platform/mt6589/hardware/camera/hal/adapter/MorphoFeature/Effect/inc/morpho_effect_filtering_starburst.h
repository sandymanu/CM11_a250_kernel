/**
 * @file    morpho_effect_filtering_starburst.h
 * @brief   Morpho Filtering Effect "STARBURST" module.
 *
 * effect_name     ...  "ES_STARBURST"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_STARBURST_H
#define MORPHO_EFFECT_FILTERING_STARBURST_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * ES_STARBURST エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int strength;		/* STARBURST強度(0～256) default:128 */
    int starcount;	/* STARBURST数(0～256) default:4 */
} morpho_EffectFilteringStarburstParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_STARBURST_H */
