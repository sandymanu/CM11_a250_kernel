#ifndef MORPHO_EFFECT_FILTERING_COMIC_H
#define MORPHO_EFFECT_FILTERING_COMIC_H

#ifdef __cplusplus
extern "C" {
#endif

enum {
    MORPHO_EFFECT_FILTERING_COMIC_EDGE_SOBEL = 0,
    MORPHO_EFFECT_FILTERING_COMIC_EDGE_PREWITT,
    MORPHO_EFFECT_FILTERING_COMIC_EDGE_LAPLACIAN,
    MORPHO_EFFECT_FILTERING_COMIC_EDGE_NUM,
};

typedef struct {
    int gaussian;
    int edge_kernel;
    int edge_a; // 170
    int edge_b; // 200
    int intensy_a; // 0.17f
    int thinning;
    int target_width;
    int target_height;
} morpho_EffectFilteringComicParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif
