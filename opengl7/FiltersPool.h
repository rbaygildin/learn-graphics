//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_FILTERSPOOL_H
#define OPENGL_FILTERSPOOL_H

#include "filters/BlueFilter.h"
#include "filters/BlurFilter.h"
#include "filters/GreenFilter.h"
#include "filters/RedFilter.h"
#include "filters/SepiaFilter.h"
#include "filters/GammaFilter.h"
#include "filters/Original.h"
#include "filters/AberrationFilter.h"
#include "filters/DistractionFilter.h"
#include "filters/Emboss.h"
#include "filters/GrayscaleFilter.h"
#include "filters/ReflectionFilter.h"
#include "filters/SharpenFilter.h"
#include "filters/ThresholdingFilter.h"
#include "filters/ColorBalance.h"
#include "filters/Ripple.h"
#include "filters/Kernel.h"
#include "filters/Canny.h"
#include "filters/Lap.h"

class FiltersPool {
public:
    static FiltersPool *getInstance();

    BlurFilter *blurFilter();

    RedFilter *redFilter();

    GreenFilter *greenFilter();

    BlueFilter *blueFilter();

    SepiaFilter *sepiaFilter();

    GammaFilter *gammaFilter(float gamma = 2.2);

    AberrationFilter *aberrationFilter();

    DistractionFilter *distractionFilter();

    Emboss *emboss();

    GrayscaleFilter *grayscaleFilter();

    ReflectionFilter *reflectionFilter();

    SharpenFilter *sharpenFilter();

    ThresholdingFilter *thresholdingFilter(float threshold = 0.5);

    ColorBalance *colorBalance(float r = 1.0, float g = 1.0, float b = 1.0);

    Ripple *ripple(float time = 2.0, float step = 10.0);

    Original *original();

    Kernel *kernel(float k[]);

    Canny *canny(float d);

    Lap *lap();

private:
    FiltersPool();

    ~FiltersPool();

private:
    static FiltersPool *instance;

private:
    BlueFilter *_blueFilter;
    BlurFilter *_blurFilter;
    GreenFilter *_greenFilter;
    RedFilter *_redFilter;
    SepiaFilter *_sepiaFilter;
    GammaFilter *_gammaFilter;
    Original *_original;
    DistractionFilter *_distaction;
    AberrationFilter *_aberration;
    Emboss *_emboss;
    GrayscaleFilter *_grayscale;
    ReflectionFilter *_reflection;
    SharpenFilter *_sharpen;
    ThresholdingFilter *_thresholding;
    ColorBalance *_colorBalance;
    Ripple *_ripple;
    Kernel *_kernel;
    Lap* _lap;
    Canny *_canny;
};


#endif //OPENGL_FILTERSPOOL_H
