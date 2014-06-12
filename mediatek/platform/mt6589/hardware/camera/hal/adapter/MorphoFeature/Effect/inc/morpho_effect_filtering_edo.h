/**
 * @file    morpho_effect_filtering_edo.h
 * @brief   Morpho Filtering Effect "Edo" module.
 *
 * effect_name     ...  "ES_EDO"
 * needs_image_num ...  1
 *
 * @author Ola Nordqvist (n-ola@morphoinc.com)
 * Copyright (C) 2010 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_EDO_H
#define MORPHO_EFFECT_FILTERING_EDO_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * ES_EDO エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int age; /**< 未実装 */
} morpho_EffectFilteringEdoParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_EDO_H */
