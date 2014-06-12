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
 * ES_BALLOON �G�t�F�N�g�̃p�����[�^.
 * morpho_EffectEngine_setEffectParam() �Őݒ肵�Ă��������B
 */
typedef struct {
    int use_external_rect;      /* �O������̊��`�w����g�p���邩�ǂ����B 0..�g�p���Ȃ��B 1..�g�p����B*/
    morpho_RectInt face_rects[MORPHO_EFFECT_FILTERING_BALLOON_MAX_FACE_RECTS];  /* ���` */
    int angles[MORPHO_EFFECT_FILTERING_BALLOON_MAX_FACE_RECTS]; /* ���`�̌��� MORPHO_EFFECT_ENGINE_INCLINATION_�`�Ŏw��*/
    int rect_num;               /* ���`�� */
} morpho_EffectFilteringBalloonParam;

typedef struct {
    int num_processed;     /* ����������̌� */
} morpho_EffectFilteringBalloonStatus;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_BALLOON_H */