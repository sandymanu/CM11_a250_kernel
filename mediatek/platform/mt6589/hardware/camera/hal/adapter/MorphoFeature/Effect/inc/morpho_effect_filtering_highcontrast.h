/**
 * @file    morpho_effect_filtering_highcontrast.h
 * @brief   Morpho Filtering Effect "HIGHCONTRAST" module.
 *
 * effect_name     ...  "ES_HIGHCONTRAST"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_HIGHCONTRAST_H
#define MORPHO_EFFECT_FILTERING_HIGHCONTRAST_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * ES_HIGHCONTRAST エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int strength;   /* HICONTRAST強度 */
    int darkedge;   /* 周囲を暗くするかどうか */
} morpho_EffectFilteringHighcontrastParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_HIGHCONTRAST_H */
