//
// Created by Max Heartfield on 15.03.18.
//

#include "FiltersPool.h"
#include "filters/DistractionFilter.h"
#include "filters/Kernel.h"

#define VEC2(x, y) (QVector2D(x, y))

FiltersPool *FiltersPool::instance;

FiltersPool *FiltersPool::getInstance() {
    if (instance == nullptr)
        instance = new FiltersPool;
    return instance;
}

FiltersPool::FiltersPool() {
    _blueFilter = new BlueFilter;
    _blurFilter = new BlurFilter;
    _greenFilter = new GreenFilter;
    _redFilter = new RedFilter;
    _sepiaFilter = new SepiaFilter;
    _gammaFilter = new GammaFilter;
    _aberration = new AberrationFilter;
    _distaction = new DistractionFilter;
    _emboss = new Emboss;
    _grayscale = new GrayscaleFilter;
    _reflection = new ReflectionFilter;
    _sharpen = new SharpenFilter;
    _thresholding = new ThresholdingFilter;
    _colorBalance = new ColorBalance;
    _ripple = new Ripple;
    _kernel = new Kernel;
    _canny = new Canny;
    _lap = new Lap;
    _original = new Original;
}

FiltersPool::~FiltersPool() {
    delete _blueFilter;
    delete _blurFilter;
    delete _greenFilter;
    delete _redFilter;
    delete _sepiaFilter;
}

BlurFilter *FiltersPool::blurFilter() {
    return _blurFilter;
}

RedFilter *FiltersPool::redFilter() {
    return _redFilter;
}

GreenFilter *FiltersPool::greenFilter() {
    return _greenFilter;
}

BlueFilter *FiltersPool::blueFilter() {
    return _blueFilter;
}

SepiaFilter *FiltersPool::sepiaFilter() {
    return _sepiaFilter;
}

GammaFilter *FiltersPool::gammaFilter(float gamma) {
    _gammaFilter->bind();
    _gammaFilter->setUniformValue("gamma", gamma);
    return _gammaFilter;
}


Original *FiltersPool::original() {
    return _original;
}

DistractionFilter *FiltersPool::distractionFilter() {
    return _distaction;
}

AberrationFilter *FiltersPool::aberrationFilter() {
    return _aberration;
}

Emboss *FiltersPool::emboss() {
    return _emboss;
}

GrayscaleFilter *FiltersPool::grayscaleFilter() {
    return _grayscale;
}

ReflectionFilter *FiltersPool::reflectionFilter() {
    return _reflection;
}

SharpenFilter *FiltersPool::sharpenFilter() {
    return _sharpen;
}

ThresholdingFilter *FiltersPool::thresholdingFilter(float threshold) {
    _thresholding->bind();
    _thresholding->setUniformValue("threshold", threshold);
    return _thresholding;
}

ColorBalance *FiltersPool::colorBalance(float r, float g, float b) {
    _colorBalance->bind();
    _colorBalance->setUniformValue("redLevel", r);
    _colorBalance->setUniformValue("greenLevel", g);
    _colorBalance->setUniformValue("blueLevel", b);
    return _colorBalance;
}

Ripple *FiltersPool::ripple(float time, float step) {
    _ripple->bind();
    _ripple->setUniformValue("time", time);
    _ripple->setUniformValue("step", step);
    return _ripple;
}

Kernel *FiltersPool::kernel(float k[]) {
    if (k == nullptr)
        k = new float[9]{1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f};
    _kernel->bind();
    QVector2D offset[9];
    offset[0] = VEC2(-1.f, -1.f);
    offset[1] = VEC2(0.f, -1.f);
    offset[2] = VEC2(1.f, -1.f);
    offset[3] = VEC2(-1.f, 0.f);
    offset[4] = VEC2(0.f, 0.f);
    offset[5] = VEC2(1.f, 0.f);
    offset[6] = VEC2(-1.f, 1.f);
    offset[7] = VEC2(0.f, 1.f);
    offset[8] = VEC2(1.f, 1.f);
    _kernel->setUniformValueArray("offset", offset, 9);
    _kernel->setUniformValueArray("kernel", k, 9, 1);
    return _kernel;
}

Canny *FiltersPool::canny(float threshold = 0.5) {
    _canny->bind();
    _canny->setUniformValue("threshold", threshold);
    return _canny;
}

Lap *FiltersPool::lap() {
    return _lap;
}


