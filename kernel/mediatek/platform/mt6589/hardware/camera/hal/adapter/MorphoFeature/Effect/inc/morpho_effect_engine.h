/**
 * @file    morpho_effect_engine.h
 * @brief   Morpho Effect Engine module.
 *
 * Copyright (C) 2012 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_ENGINE_H
#define MORPHO_EFFECT_ENGINE_H

#include "morpho_primitive.h"
#include "morpho_api.h"
#include "morpho_error.h"
#include "morpho_image_data.h"
#include "morpho_rect_int.h"

#define MORPHO_EFFECT_ENGINE_VER "Morpho Effect Library Ver.3.1.0.Tinno 2013/04/09" /* Version string */

#ifdef __cplusplus
extern "C" {
#endif

/* Effect Engine */
typedef struct {
    void *p;
} morpho_EffectEngine;

/** ライブラリバージョン取得.
 *
 * @return ライブラリのバージョン..
 */
MORPHO_API(const char *)
morpho_EffectEngine_getVersion( void );

enum {
    MORPHO_EFFECT_ENGINE_MEMORY_TYPE_NONE, /**< 入力画像コピーしない */
    MORPHO_EFFECT_ENGINE_MEMORY_TYPE_COPY, /**< 入力画像をそのままコピーする */
    MORPHO_EFFECT_ENGINE_MEMORY_TYPE_NUM,
};

enum {
/**<   0° 顔が上向きの状態、眼が口よりもy座標が小さい */
    MORPHO_EFFECT_ENGINE_INCLINATION_0   = 0x00000001,
/**< 90°  反時計周り */
    MORPHO_EFFECT_ENGINE_INCLINATION_90  = 0x00000002,
/**< 180° 反時計周り */
    MORPHO_EFFECT_ENGINE_INCLINATION_180 = 0x00000004,
/**< 270° 反時計周り */
    MORPHO_EFFECT_ENGINE_INCLINATION_270 = 0x00000008,
    MORPHO_EFFECT_ENGINE_INCLINATION_NUM = 4,
};

/** 指定のエフェクトエンジンの実行に必要なバッファサイズの取得.
 *
 * @param[in] effect_name       エフェクト文字列
 * @param[in] format_name       フォーマット文字列
 * @param[in] max_input_width   最大入力画像幅
 * @param[in] max_input_heigh   最大入力画像高さ
 * @param[in] output_width      出力画像幅
 * @param[in] output_height     出力画像高さ
 * @param[in] max_image_num     登録画像数
 * @param[in] memory_type       メモリ確保種別    
 *               MORPHO_EFFECT_ENGINE_MEMORY_TYPE_NONE   :入力画像コピーしない  
 *               MORPHO_EFFECT_ENGINE_MEMORY_TYPE_NORMAL :入力画像をそのままコピーする
 *
 * @return 必要なバッファサイズ(エラーの場合は0を返す).
 */
MORPHO_API(int)
morpho_EffectEngine_getBufferSize( const char *effect_name, const char *format_name, int max_input_width, int max_input_height, int output_width, int output_height, int max_image_num, int memory_type);

/** 指定のエフェクトエンジンの実行に必要なバッファサイズの取得(getFaceRectを使用する場合).
 *
 * @param[in] effect_name       エフェクト文字列
 * @param[in] format_name       フォーマット文字列
 * @param[in] max_input_width   最大入力画像幅
 * @param[in] max_input_heigh   最大入力画像高さ
 * @param[in] output_width      出力画像幅
 * @param[in] output_height     出力画像高さ
 * @param[in] max_image_num     登録画像数
 * @param[in] memory_type       メモリ確保種別    
 *               MORPHO_EFFECT_ENGINE_MEMORY_TYPE_NONE   :入力画像コピーしない  
 *               MORPHO_EFFECT_ENGINE_MEMORY_TYPE_NORMAL :入力画像をそのままコピーする
 *
 * @return 必要なバッファサイズ(エラーの場合は0を返す).
 */
MORPHO_API(int)
morpho_EffectEngine_getBufferSizeWithFace( const char *effect_name, const char *format_name, int max_input_width, int max_input_height, int output_width, int output_height, int max_image_num, int memory_type);


/** エフェクトエンジンの初期化.
 *
 * @param[in] p_effect_engine   エフェクトエンジンへのポインタ.
 * @param[in] effect_name       エフェクト文字列
 * @param[in] format_name       フォーマット文字列
 * @param[in] buffer            エフェクトエンジンに渡すバッファのポインタ.
 * @param[in] buffer_size       エフェクトエンジンに渡すバッファのサイズ.
 * @param[in] max_input_width   最大入力画像幅.
 * @param[in] max_input_height  最大入力画像高さ.
 * @param[in] output_width      出力画像幅
 * @param[in] output_height     出力画像高さ
 * @param[in] max_image_num     登録画像数.
 * @param[in] memory_type       メモリ確保種別.
 *               MORPHO_EFFECT_ENGINE_MEMORY_TYPE_NONE   :入力画像コピーしない  
 *               MORPHO_EFFECT_ENGINE_MEMORY_TYPE_NORMAL :入力画像をそのままコピーする
 *
 * @return MORPHO_OK            : 成功
 *         MORPHO_ERROR_PARAM   : パラメータ異常
 * 
 */
/* Effect Name
    "ES_GREENY",
    "ES_COMIC",
    "ES_MONA",
    "ES_HIGHCONTRAST",
    "ES_BACKLIGHT",
    "ES_NOSTALGY",
    "ES_POPART",
    "ES_PARTCOLOR",
    "ES_POSTER",
    "ES_PRETTY",
    "ES_SMILE",
    "ES_THERMO",
    "ES_MOZA",
    "EM_RELIC",
    "ES_EDO",
    "ES_SEPIAN",
    "ES_INFRARED",
    "ES_LIGHTEN",
    "ES_OVEREXPOSE",
    "EM_TWINKLE",
    "ES_DEFOCUS",
    "ES_MINIATURE",
    "ES_STARBURST",
    "ES_BALLOON",
    "ES_PENCIL",
    "EM_HARRIS",
    "ES_VIVID",
    "ES_FISHEYE1",
    "ES_KALEIDOSCOPE",
    "ES_MIRROR",
    "ES_COLORFILTER",
    "ES_SELECTCOLOR",
    "ES_PINFOCUS",
    "ES_NEGATIVE",
    "ES_SOLARIZE",
    "ES_REDSCALE",
    "ES_NATURE",
    "ES_WARM",
    "ES_BAKE",
    "ES_COUNTRY",
    "ES_WAVE",
    "ES_GLASS",
*/
MORPHO_API(int)
morpho_EffectEngine_initialize( morpho_EffectEngine *p_effect_engine, const char *effect_name, const char *format_name,
                                void *buffer, int buffer_size, int max_input_width, int max_input_height,
                                int output_width, int output_height, int max_image_num, int memory_type);

/** 入力画像必要数の取得.
 *
 * @param[in]  p_effect_name       エフェクト文字列.
 * @param[out] p_min_image_num     最小入力枚数.
 * @param[out] p_max_image_num     最大入力枚数.
 *
 * @return Required memory size if 成功. If fails, returns 0.
 */
MORPHO_API(int)
morpho_EffectEngine_getNeedsImageNum( const char *effect_name, int *p_min_image_num, int *p_max_image_num);

/** Level粒度の取得.
 *
 * @param[in]  p_effect_engine     エフェクトエンジンへのポインタ.
 * @param[out] p_level_granu       Level粒度.
 *
 * @return MORPHO_OK            : 成功
 *         MORPHO_ERROR_PARAM   : パラメータ異常
 */
MORPHO_API(int)
morpho_EffectEngine_getLevelGranu( morpho_EffectEngine *p_effect_engine, int *p_level_granu);

/** Progress粒度の取得.
 *
 * @param[in]  p_effect_engine     エフェクトエンジンへのポインタ.
 * @param[out] p_progress_granu    Progress粒度.
 *
 * @return MORPHO_OK            : 成功
 *         MORPHO_ERROR_PARAM   : パラメータ異常
 */
MORPHO_API(int)
morpho_EffectEngine_getProgressGranu( morpho_EffectEngine *p_effect_engine, int *p_progress_granu);

/** エフェクトエンジンの終了.
 *
 * @param[in] p_effect_engine  エフェクトエンジンへのポインタ
 *
 * @return 0 if 成功. -1 if fails.
 */
MORPHO_API(int)
morpho_EffectEngine_finalize( morpho_EffectEngine *p_effect_engine );


/** 入力画像(morpho_ImageData形式)の登録.
 *
 * @param[in]  p_effect_engine エフェクトエンジンへのポインタ.
 * @param[in]  p_input_image   入力画像.
 * @param[out] p_image_id      画像ID.
 *
 * @return MORPHO_OK            : 成功.
 *         MORPHO_ERROR_PARAM   : パラメータ異常.
 *
 */
MORPHO_API(int) 
morpho_EffectEngine_registerImage( morpho_EffectEngine *p_effect_engine, const morpho_ImageData *p_input_image, int *p_image_id );


/** 入力画像の解放.
 *
 * @param[in]  p_effect_engine エフェクトエンジンへのポインタ.
 * @param[in]  image_id        画像ID.
 *
 * @return MORPHO_OK            : 成功.
 *         MORPHO_ERROR_PARAM   : パラメータ異常.
 *
 */
MORPHO_API(int) 
morpho_EffectEngine_releaseImage( morpho_EffectEngine *p_effect_engine, int image_id );

/** エフェクトの開始.
 *
 * @param[in]   p_effect_engine エフェクトエンジンへのポインタ.
 * @param[in]   image_ids       画像ID(配列).
 * @param[in]   image_num       画像数.
 * @param[out]  p_output_image  出力画像.
 * @param[in]   p_rect          出力矩形.
 * @param[in]   level           エフェクト度合(0～32768).
 *
 * @return MORPHO_OK            : 成功.
 *         MORPHO_ERROR_PARAM   : パラメータ異常.
 *         MORPHO_ERROR_STATE   : 状態異常.
 *
 */
MORPHO_API(int) 
morpho_EffectEngine_start( morpho_EffectEngine *p_effect_engine, int *image_ids, int image_num, morpho_ImageData *p_output_image, 
                           const morpho_RectInt *p_rect, int level);


/** エフェクトの実行（分割処理）.
 *
 * @param[in]   p_effect_engine エフェクトエンジンへのポインタ.
 * @param[in]   progress        処理進捗度(0～32768). 処理が重いときの処理分割用.
 *
 * @return MORPHO_OK            : 処理完了.
 *         MORPHO_DOPROCESS     : 処理未完了.
 *         MORPHO_ERROR_PARAM   : パラメータ異常.
 *         MORPHO_ERROR_STATE   : 状態異常.
 *
 */
MORPHO_API(int) 
morpho_EffectEngine_run( morpho_EffectEngine *p_effect_engine, int progress );

/** エフェクトの終了.
 *
 * @param[in]   p_effect_engine エフェクトエンジンへのポインタ.
 *
 * @return MORPHO_OK            : 成功.
 *         MORPHO_ERROR_PARAM   : パラメータ異常.
 *         MORPHO_ERROR_STATE   : 状態異常.
 *
 */
MORPHO_API(int) 
morpho_EffectEngine_stop( morpho_EffectEngine *p_effect_engine);


/** エフェクトパラメータ指定.
 *
 * @param[in]   p_effect_engine エフェクトエンジンへのポインタ.
 * @param[in]   p_param         エフェクトパラメータ.
 *
 * @return MORPHO_OK            : 成功.
 *         MORPHO_ERROR_PARAM   : パラメータ異常.
 *
 */
MORPHO_API(int) 
morpho_EffectEngine_setEffectParam( morpho_EffectEngine *p_effect_engine, const void *p_param);

/** エフェクトパラメータ取得.
 *
 * @param[in]   p_effect_engine エフェクトエンジンへのポインタ.
 * @param[out]  p_param         エフェクトパラメータ.
 *
 * @return MORPHO_OK            : 成功.
 *         MORPHO_ERROR_PARAM   : パラメータ異常.
 *
 */
MORPHO_API(int) 
morpho_EffectEngine_getEffectParam( morpho_EffectEngine *p_effect_engine, void *p_param);

/** ステータスの取得.
 *
 * @param[in]   p_effect_engine エフェクトエンジンへのポインタ.
 * @param[out]  p_status        ステータス.
 *
 * @return MORPHO_OK            : 成功.
 *         MORPHO_ERROR_PARAM   : パラメータ異常.
 *
 */MORPHO_API(int) 
morpho_EffectEngine_getStatus( morpho_EffectEngine *p_effect_engine, void *p_status);

    
/*******************  拡張関数群 **********************/

/** 顔検出矩形の取得.
 *
 * @param[in]   p_effect_engine エフェクトエンジンへのポインタ.
 * @param[in]   image_id        画像ID.
 * @param[out]  p_rect          顔検出矩形への配列.
 * @param[out]  p_angles        顔矩形の向きへの配列.
 * @param[out]  p_smile_levels  笑顔レベルへの配列.
 * @param[in]   array_num       顔検出矩形、笑顔レベルの配列数.
 * @param[out]  p_face_num      顔検出矩形及び笑顔レベルの数.
 *
 * @return MORPHO_OK            : 成功.
 *         MORPHO_ERROR_PARAM   : パラメータ異常.
 *
 * array_numには、p_rectの配列数を指定してください。本APIを抜けたとき、*p_face_numに実際に取得できた顔検出矩形数が入ります。
 * このAPIの中で顔検出を実行します。
 */
MORPHO_API(int) 
morpho_EffectEngine_getFaceRect( morpho_EffectEngine *p_effect_engine, int image_id, morpho_RectInt *p_rects, int *p_angles, int *p_smile_levels, int array_num,  int* p_face_num );


/*******************  ユーティリティ関数群 **********************/

/** エフェクト画像のワンショット描画（処理分割不要）.
 *
 * @param[in]   p_effect_engine エフェクトエンジンへのポインタ.
 * @param[in]   image_ids       画像ID(配列).
 * @param[in]   image_num       画像数.
 * @param[out]  p_output_image  出力画像.
 * @param[in]   p_rect          出力矩形.
 * @param[in]   level           エフェクト度合(0～32768).
 *
 * @return MORPHO_OK            : 成功.
 *         MORPHO_ERROR_PARAM   : パラメータ異常.
 *
 * 以下の処理を実行します。
 *   {
 *     int r = 0;
 *     r |= start(p_effect_engine, image_ids, image_num, p_output_image, p_rect, level);
 *     r |= run(p_effect_engine, 32768);
 *     r |= stop(p_effect_engine);
 *     return r;
 *   }
 * 
 */
MORPHO_API(int) 
morpho_EffectEngine_drawOneShot( morpho_EffectEngine *p_effect_engine, int *image_ids, int image_num, morpho_ImageData *p_output_image, 
                                 const morpho_RectInt *p_rect, int level);


#ifdef MORPHO_EFFECT_ZTE
MORPHO_API(int)
morpho_EffectEngine_setVideoMode(morpho_EffectEngine *p_effect_engine, int video_mode);

MORPHO_API(int)
morpho_EffectEngine_setSkipFrameNum(morpho_EffectEngine *p_effect_engine , int skip_frame_num);
#endif

#ifdef __cplusplus
}
#endif

#endif /* MORPHO_EFFECT_ENGINE_H */
