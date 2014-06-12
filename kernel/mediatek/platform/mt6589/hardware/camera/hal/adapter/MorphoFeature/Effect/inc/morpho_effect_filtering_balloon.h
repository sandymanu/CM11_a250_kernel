/**
 * @file    morpho_effect_filtering_balloon.h
 * @brief   Morpho Filtering Effect "Balloon" module.
 *
 * effect_name     ...  "ES_BALLOON"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_BALLOON_H
#define MORPHO_EFFECT_FILTERING_BALLOON_H

#include "morpho_rect_int.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MORPHO_EFFECT_FILTERING_BALLOON_MAX_FACE_RECTS  10
    
/**  
 * ES_BALLOON エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int use_external_rect;      /* 外部からの顔矩形指定を使用するかどうか。 0..使用しない。 1..使用する。*/
    morpho_RectInt face_rects[MORPHO_EFFECT_FILTERING_BALLOON_MAX_FACE_RECTS];  /* 顔矩形 */
    int angles[MORPHO_EFFECT_FILTERING_BALLOON_MAX_FACE_RECTS]; /* 顔矩形の向き MORPHO_EFFECT_ENGINE_INCLINATION_～で指定*/
    int rect_num;               /* 顔矩形数 */
} morpho_EffectFilteringBalloonParam;

typedef struct {
    int num_processed;     /* 処理した顔の個数 */
} morpho_EffectFilteringBalloonStatus;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_BALLOON_H */
