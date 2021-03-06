/* This file is part of Into.
 * Copyright (C) Intopii 2013.
 * All rights reserved.
 *
 * Licensees holding a commercial Into license may use this file in
 * accordance with the commercial license agreement. Please see
 * LICENSE.commercial for commercial licensing terms.
 *
 * Alternatively, this file may be used under the terms of the GNU
 * Affero General Public License version 3 as published by the Free
 * Software Foundation. In addition, Intopii gives you special rights
 * to use Into as a part of open source software projects. Please
 * refer to LICENSE.AGPL3 for details.
 */

#ifndef _PIIORIENTATIONESTIMATOR_H
#define _PIIORIENTATIONESTIMATOR_H

#include <PiiDefaultOperation.h>
#include <PiiMatrix.h>
#include <PiiFft.h>

/**
 * An operation that estimates the orientation of texture. For each
 * input image, an orientation histogram is calculated. The number of
 * quantization levels can be set by the `angles` property.
 *
 * Inputs
 * ------
 *
 * @in image - input image. Any gray level or color image.
 *
 * Outputs
 * -------
 *
 * @out histogram - orientation histogram. Prominent peaks mean
 * prominent orientations. Each bin in the histogram denotes the
 * strength of texture orientation at a certain discrete angle. Note
 * that the orientation histogram represents the direction of image
 * gradient or "slope". A gradient pointing at 135 degrees means an
 * oriented element pointing at 45 or 225 degrees. To get texture
 * orientation instead of gradient direction, set the [rotateHistogram]
 * flag to `true`. (PiiMatrix<float>)
 *
 */
class PiiOrientationEstimator : public PiiDefaultOperation
{
  Q_OBJECT

  /**
   * The number of quantization levels for the orientation angle. The
   * default value is 180. This number defines the length of the
   * orientation histogram. Note that it is not possible to use the
   * full circle with the FFT. Only the gradient-based estimator can
   * also measure "slope direction". For the gradient-based estimator,
   * the default quantization step is thus 360/180 = 2 degrees. For
   * other estimators, the default value means 1 degree accuracy.
   */
  Q_PROPERTY(int angles READ angles WRITE setAngles);

  /**
   * The type of orientation estimation. Different methods have
   * different strengths and weaknesses. The default is
   * `UnidirectionalGradient`.
   */
  Q_PROPERTY(EstimationType estimationType READ estimationType WRITE setEstimationType);
  Q_ENUMS(EstimationType);

  /**
   * Rotate the orientation histogram by 90 degrees. This effectively
   * gives you the texture orientation instead of gradient direction.
   * The default value is `false`.
   */
  Q_PROPERTY(bool rotateHistogram READ rotateHistogram WRITE setRotateHistogram);

  /**
   * Output normalization. If set to `true` (the default), the output
   * histogram will always sum up to unity. Otherwise, the sum depends
   * on input image size, gradient magnitudes etc.
   */
  Q_PROPERTY(bool normalized READ normalized WRITE setNormalized);

  PII_OPERATION_SERIALIZATION_FUNCTION
public:
  /**
   * Different ways of estimating texture orientation.
   *
   * - `Gradient` - local gradient based method. Works well in most
   * cases, especially within small image windows. Faster than the
   * Fourier-based technique. The gradient method separates
   * orientations pointing to opposite directions and thus measures
   * orientation over a full circle.
   *
   * - `UnidirectionalGradient` - same as `Gradient`, but combines
   * orientations pointing to opposite directions, thus using only
   * half of the orientation circle.
   *
   * - `Fourier` - Fourier transform based method. Captures weak
   * repeating structures better than the gradient method. Typically
   * requires larger samples than `Gradient` and is somewhat slower.
   */
  enum EstimationType { Gradient, UnidirectionalGradient, Fourier };

  PiiOrientationEstimator();

  void check(bool reset);

protected:
  void process();

  int angles() const;
  void setAngles(int angles); // 0.1 dgr is max
  EstimationType estimationType() const;
  void setEstimationType(EstimationType estimationType);
  void setRotateHistogram(bool rotateHistogram);
  bool rotateHistogram() const;
  void setNormalized(bool normalize);
  bool normalized() const;

private:
  template <class ColorType> void colorOrientation(const PiiVariant& obj);
  template <class T> void grayOrientation(const PiiVariant& obj);
  template <class T> void estimateOrientation(const PiiMatrix<T>& img);
  template <class T> void estimateGradient(const PiiMatrix<T>& img);
  template <class T> void estimateFourier(const PiiMatrix<T>& img);

  // Non-template implementations to reduce code bloat
  void estimateGradient(const PiiMatrix<float>& gradientX,
                        const PiiMatrix<float>& gradientY);
  void estimateFourierFloat(PiiMatrix<float>& img);

  // Rotate histogram if needed and emit it
  void emitHistogram(PiiMatrix<float>& histogram);

  /// @internal
  class Data : public PiiDefaultOperation::Data
  {
  public:
    Data();

    PiiInputSocket* pImageInput;
    PiiOutputSocket* pHistogramOutput;

    int iAngles;
    EstimationType estimationType;
    bool bRotateHistogram;
    bool bNormalized;

    PiiFft<float> fft;
  };
  PII_D_FUNC;

  static PiiMatrix<float> _gradientFilterX, _gradientFilterY;
};


#endif //_PIIORIENTATIONESTIMATOR_H
