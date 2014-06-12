/**
 * @file    morpho_effect_filtering_pencil.h
 * @brief   Morpho Filtering Effect "Pencil" module.
 *
 * effect_name     ...  "ES_PENCIL"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_PENCIL_H
#define MORPHO_EFFECT_FILTERING_PENCIL_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * ES_PENCIL エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int touch;       /* 筆タッチの方向（4：エッジに沿って、5:エッジに垂直、0～3：水平、斜め（右下）、垂直、斜め（右上）） */
    int saturation;  /* 彩度(0-256)*/
    int target_width;
    int target_height;
} morpho_EffectFilteringPencilParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_PENCIL_H */
