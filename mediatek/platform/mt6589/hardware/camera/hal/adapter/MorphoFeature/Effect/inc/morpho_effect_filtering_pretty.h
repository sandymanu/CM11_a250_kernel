/**
 * @file    morpho_effect_filtering_pretty.h
 * @brief   Morpho Filtering Effect "Pretty" module.
 *
 * effect_name     ...  "ES_PRETTY"
 * needs_image_num ...  1
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_PRETTY_H
#define MORPHO_EFFECT_FILTERING_PRETTY_H

#include "morpho_rect_int.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MORPHO_EFFECT_FILTERING_PRETTY_MAX_FACE_RECTS  10
    
/**  
 * ES_PRETTY エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
/* 美肌補正用パラメータ */
    unsigned char ideal_r;  /* 補正目標画素値(R) 0～255 */
    unsigned char ideal_g;  /* 補正目標画素値(G) 0～255 */
    unsigned char ideal_b;  /* 補正目標画素値(B) 0～255 */
    int strength;           /* 理想にどこまで近づけるか(0-256) */
/* 小顔補正用パラメータ */
    int face_smallness;   /* 顔の小ささ(0～256) */
/* 目補正用パラメータ */
    int eye_vividness;    /* 目の黒さ(0～256) */
    int eye_wideness;     /* 目の大きさ(0～256) */
    int eye_sharpness;    /* 目のくっきり度合い(0～256) */
    int eyelash_mode;     /* 0..まつ毛補正なし  1..まつ毛補正1  2..まつ毛補正2 3..まつ毛補正3 */
    int red_eye;          /* 赤目補正レベル(0～256) 0で補正なし。値が大きいほど強く補正 */
    
    int use_external_rect;      /* 外部からの顔矩形指定を使用するかどうか。 0..使用しない。 1..使用する。*/
    morpho_RectInt face_rects[MORPHO_EFFECT_FILTERING_PRETTY_MAX_FACE_RECTS];  /* 顔矩形 */
    int angles[MORPHO_EFFECT_FILTERING_PRETTY_MAX_FACE_RECTS]; /* 顔矩形の向き MORPHO_EFFECT_ENGINE_INCLINATION_～で指定*/
    int rect_num;               /* 顔矩形数 */

    int beauty;           /* 美顔処理 1:行う 0:行わない 初期値 0 */
} morpho_EffectFilteringPrettyParam;

typedef struct {
    int num_processed;     /* 処理した顔の個数 */
} morpho_EffectFilteringPrettyStatus;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_PRETTY_H */
