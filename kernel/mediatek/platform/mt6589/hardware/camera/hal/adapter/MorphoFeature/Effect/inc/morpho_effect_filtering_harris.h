/**
 * @file    morpho_effect_filtering_harris.h
 * @brief   Morpho Filtering Effect "HARRIS" module.
 *
 * effect_name     ...  "EM_HARRIS"
 * needs_image_num ...  1-
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_FILTERING_HARRIS_H
#define MORPHO_EFFECT_FILTERING_HARRIS_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * EM_HARRIS エフェクトのパラメータ.
 * morpho_EffectEngine_setEffectParam() で設定してください。
 */
typedef struct {
    int green_delay;      /**< 緑成分を何フレーム分遅らせるか(1～3)：デフォルト 3 */
    int blue_delay;       /**< 青成分を何フレーム分遅らせるか(1～6)：デフォルト 6 */
    int skip_frame_num;   /**< 何フレームおきに保存するか  (0～256)：デフォルト 0 */

   /* 各成分は ***_delay * (skip_frame_num + 1) フレーム遅れて表示される */
} morpho_EffectFilteringHarrisParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_FILTERING_HARRIS_H */
