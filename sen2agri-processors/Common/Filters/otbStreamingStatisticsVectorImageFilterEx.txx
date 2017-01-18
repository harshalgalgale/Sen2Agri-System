/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbStreamingStatisticsVectorImageFilter_txx
#define otbStreamingStatisticsVectorImageFilter_txx
#include "otbStreamingStatisticsVectorImageFilter.h"

#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"
#include "itkProgressReporter.h"
#include "otbMacro.h"

namespace otb
{

template<class TInputImage, class TPrecision>
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::PersistentStreamingStatisticsVectorImageFilterEx()
 : m_EnableMinMax(true),
   m_EnableFirstOrderStats(true),
   m_EnableSecondOrderStats(true),
   m_UseUnbiasedEstimator(true),
   m_IgnoreInfiniteValues(true),
   m_IgnoreUserDefinedValue(false),
   m_UserIgnoredValue(itk::NumericTraits<InternalPixelType>::Zero)
{
  // first output is a copy of the image, DataObject created by
  // superclass

  // allocate the data objects for the outputs which are
  // just decorators around vector/matrix types
  for (unsigned int i = 1; i < 10; ++i)
    {
    this->itk::ProcessObject::SetNthOutput(i, this->MakeOutput(i).GetPointer());
    }
  // Initiate ignored pixel counters
  m_IgnoredInfinitePixelCount= std::vector<itk::VariableLengthVector<unsigned int>>(this->GetNumberOfThreads(), itk::VariableLengthVector<unsigned int>(0));
  m_IgnoredUserPixelCount= std::vector<itk::VariableLengthVector<unsigned int>>(this->GetNumberOfThreads(), itk::VariableLengthVector<unsigned int>(0));
}

template<class TInputImage, class TPrecision>
itk::DataObject::Pointer
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::MakeOutput(DataObjectPointerArraySizeType output)
{
  switch (output)
    {
    case 0:
      return static_cast<itk::DataObject*>(TInputImage::New().GetPointer());
      break;
    case 1:
    case 2:
      // min/max
      return static_cast<itk::DataObject*>(PixelObjectType::New().GetPointer());
      break;
    case 3:
    case 4:
      // mean / sum
      return static_cast<itk::DataObject*>(RealPixelObjectType::New().GetPointer());
      break;
    case 5:
    case 6:
      // covariance / correlation
      return static_cast<itk::DataObject*>(MatrixObjectType::New().GetPointer());
      break;
    case 7:
    case 8:
    case 9:
      // component mean, component covariance, component correlation
      return static_cast<itk::DataObject*>(RealObjectType::New().GetPointer());
      break;
    default:
      // might as well make an image
      return static_cast<itk::DataObject*>(TInputImage::New().GetPointer());
      break;
    }
}

template<class TInputImage, class TPrecision>
typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::PixelObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetMinimumOutput()
{
  return static_cast<PixelObjectType*>(this->itk::ProcessObject::GetOutput(1));
}

template<class TInputImage, class TPrecision>
const typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::PixelObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetMinimumOutput() const
{
  return static_cast<const PixelObjectType*>(this->itk::ProcessObject::GetOutput(1));
}

template<class TInputImage, class TPrecision>
typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::PixelObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetMaximumOutput()
{
  return static_cast<PixelObjectType*>(this->itk::ProcessObject::GetOutput(2));
}

template<class TInputImage, class TPrecision>
const typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::PixelObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetMaximumOutput() const
{
  return static_cast<const PixelObjectType*>(this->itk::ProcessObject::GetOutput(2));
}

template<class TInputImage, class TPrecision>
typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::RealObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetComponentMeanOutput()
{
  return static_cast<RealObjectType*>(this->itk::ProcessObject::GetOutput(7));
}

template<class TInputImage, class TPrecision>
const typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::RealObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetComponentMeanOutput() const
{
  return static_cast<const RealObjectType*>(this->itk::ProcessObject::GetOutput(7));
}

template<class TInputImage, class TPrecision>
typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::RealObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetComponentCorrelationOutput()
{
  return static_cast<RealObjectType*>(this->itk::ProcessObject::GetOutput(8));
}

template<class TInputImage, class TPrecision>
const typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::RealObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetComponentCorrelationOutput() const
{
  return static_cast<const RealObjectType*>(this->itk::ProcessObject::GetOutput(8));
}


template<class TInputImage, class TPrecision>
typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::RealObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetComponentCovarianceOutput()
{
  return static_cast<RealObjectType*>(this->itk::ProcessObject::GetOutput(9));
}

template<class TInputImage, class TPrecision>
const typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::RealObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetComponentCovarianceOutput() const
{
  return static_cast<const RealObjectType*>(this->itk::ProcessObject::GetOutput(9));
}

template<class TInputImage, class TPrecision>
typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::RealPixelObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetMeanOutput()
{
  return static_cast<RealPixelObjectType*>(this->itk::ProcessObject::GetOutput(3));
}

template<class TInputImage, class TPrecision>
const typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::RealPixelObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetMeanOutput() const
{
  return static_cast<const RealPixelObjectType*>(this->itk::ProcessObject::GetOutput(3));
}

template<class TInputImage, class TPrecision>
typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::RealPixelObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetSumOutput()
{
  return static_cast<RealPixelObjectType*>(this->itk::ProcessObject::GetOutput(4));
}

template<class TInputImage, class TPrecision>
const typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::RealPixelObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetSumOutput() const
{
  return static_cast<const RealPixelObjectType*>(this->itk::ProcessObject::GetOutput(4));
}

template<class TInputImage, class TPrecision>
typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::MatrixObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetCorrelationOutput()
{
  return static_cast<MatrixObjectType*>(this->itk::ProcessObject::GetOutput(5));
}

template<class TInputImage, class TPrecision>
const typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::MatrixObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetCorrelationOutput() const
{
  return static_cast<const MatrixObjectType*>(this->itk::ProcessObject::GetOutput(5));
}

template<class TInputImage, class TPrecision>
typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::MatrixObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetCovarianceOutput()
{
  return static_cast<MatrixObjectType*>(this->itk::ProcessObject::GetOutput(6));
}

template<class TInputImage, class TPrecision>
const typename PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>::MatrixObjectType*
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GetCovarianceOutput() const
{
  return static_cast<const MatrixObjectType*>(this->itk::ProcessObject::GetOutput(6));
}

template<class TInputImage, class TPrecision>
void
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::GenerateOutputInformation()
{
  Superclass::GenerateOutputInformation();
  if (this->GetInput())
    {
    this->GetOutput()->CopyInformation(this->GetInput());
    this->GetOutput()->SetLargestPossibleRegion(this->GetInput()->GetLargestPossibleRegion());

    if (this->GetOutput()->GetRequestedRegion().GetNumberOfPixels() == 0)
      {
      this->GetOutput()->SetRequestedRegion(this->GetOutput()->GetLargestPossibleRegion());
      }
    }
}

template<class TInputImage, class TPrecision>
void
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::AllocateOutputs()
{
  // This is commented to prevent the streaming of the whole image for the first stream strip
  // It shall not cause any problem because the output image of this filter is not intended to be used.
  //InputImagePointer image = const_cast< TInputImage * >( this->GetInput() );
  //this->GraftOutput( image );
  // Nothing that needs to be allocated for the remaining outputs
}

template<class TInputImage, class TPrecision>
void
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::Reset()
{
  TInputImage * inputPtr = const_cast<TInputImage *>(this->GetInput());
  inputPtr->UpdateOutputInformation();

  unsigned int numberOfThreads = this->GetNumberOfThreads();
  unsigned int numberOfComponent = inputPtr->GetNumberOfComponentsPerPixel();

  if (m_EnableMinMax)
    {
    PixelType tempPixel;
    tempPixel.SetSize(numberOfComponent);

    tempPixel.Fill(itk::NumericTraits<InternalPixelType>::max());
    this->GetMinimumOutput()->Set(tempPixel);

    tempPixel.Fill(itk::NumericTraits<InternalPixelType>::NonpositiveMin());
    this->GetMaximumOutput()->Set(tempPixel);

    PixelType tempTemporiesPixel;
    tempTemporiesPixel.SetSize(numberOfComponent);
    tempTemporiesPixel.Fill(itk::NumericTraits<InternalPixelType>::max());
    m_ThreadMin = std::vector<PixelType>(numberOfThreads, tempTemporiesPixel);

    tempTemporiesPixel.Fill(itk::NumericTraits<InternalPixelType>::NonpositiveMin());
    m_ThreadMax = std::vector<PixelType>(numberOfThreads, tempTemporiesPixel);
    }

  if (m_EnableSecondOrderStats)
    {
    m_EnableFirstOrderStats = true;
    }

  if (m_EnableFirstOrderStats)
    {
    RealPixelType zeroRealPixel;
    zeroRealPixel.SetSize(numberOfComponent);
    zeroRealPixel.Fill(itk::NumericTraits<PrecisionType>::ZeroValue());
    this->GetMeanOutput()->Set(zeroRealPixel);
    this->GetSumOutput()->Set(zeroRealPixel);
    m_ThreadFirstOrderAccumulators.resize(numberOfThreads);
    std::fill(m_ThreadFirstOrderAccumulators.begin(), m_ThreadFirstOrderAccumulators.end(), zeroRealPixel);

    RealType zeroReal = itk::NumericTraits<RealType>::ZeroValue();
//    m_ThreadFirstOrderComponentAccumulators.resize(numberOfThreads);
//    std::fill(m_ThreadFirstOrderComponentAccumulators.begin(), m_ThreadFirstOrderComponentAccumulators.end(), zeroReal);

    }

  if (m_EnableSecondOrderStats)
    {
    MatrixType zeroMatrix;
    zeroMatrix.SetSize(numberOfComponent, numberOfComponent);
    zeroMatrix.Fill(itk::NumericTraits<PrecisionType>::Zero);
    this->GetCovarianceOutput()->Set(zeroMatrix);
    this->GetCorrelationOutput()->Set(zeroMatrix);

    m_ThreadSecondOrderAccumulators.resize(numberOfThreads);
    std::fill(m_ThreadSecondOrderAccumulators.begin(), m_ThreadSecondOrderAccumulators.end(), zeroMatrix);

    RealType zeroReal = itk::NumericTraits<RealType>::ZeroValue();
    m_ThreadSecondOrderComponentAccumulators.resize(numberOfThreads);
    std::fill(m_ThreadSecondOrderComponentAccumulators.begin(), m_ThreadSecondOrderComponentAccumulators.end(), zeroReal);
    }

  itk::VariableLengthVector<unsigned int> zeroVector(numberOfComponent);
  zeroVector.Fill(0);
  if (m_IgnoreInfiniteValues)
    {
      m_IgnoredInfinitePixelCount= std::vector<itk::VariableLengthVector<unsigned int>>(numberOfThreads, zeroVector);
    }

  if (m_IgnoreUserDefinedValue)
    {
    m_IgnoredUserPixelCount= std::vector<itk::VariableLengthVector<unsigned int>>(this->GetNumberOfThreads(), zeroVector);
    }
}

template<class TInputImage, class TPrecision>
void
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::Synthetize()
{
  TInputImage * inputPtr = const_cast<TInputImage *>(this->GetInput());
  const unsigned int nbPixels = inputPtr->GetLargestPossibleRegion().GetNumberOfPixels();
  const unsigned int numberOfComponent = inputPtr->GetNumberOfComponentsPerPixel();

  PixelType minimum;
  minimum.SetSize(numberOfComponent);
  minimum.Fill(itk::NumericTraits<InternalPixelType>::max());
  PixelType maximum;
  maximum.SetSize(numberOfComponent);
  maximum.Fill(itk::NumericTraits<InternalPixelType>::NonpositiveMin());

  RealPixelType streamFirstOrderAccumulator(numberOfComponent);
  streamFirstOrderAccumulator.Fill(itk::NumericTraits<PrecisionType>::Zero);
  MatrixType    streamSecondOrderAccumulator(numberOfComponent, numberOfComponent);
  streamSecondOrderAccumulator.Fill(itk::NumericTraits<PrecisionType>::Zero);

//  RealType streamFirstOrderComponentAccumulator = itk::NumericTraits<RealType>::Zero;
  RealType streamSecondOrderComponentAccumulator = itk::NumericTraits<RealType>::Zero;

  itk::VariableLengthVector<unsigned int> ignoredInfinitePixelCount(numberOfComponent);
  itk::VariableLengthVector<unsigned int> ignoredUserPixelCount(numberOfComponent);

  ignoredInfinitePixelCount.Fill(0);
  ignoredUserPixelCount.Fill(0);

  // Accumulate results from all threads
  const itk::ThreadIdType numberOfThreads = this->GetNumberOfThreads();
  for (itk::ThreadIdType threadId = 0; threadId < numberOfThreads; ++threadId)
    {
    if (m_EnableMinMax)
      {
        itkExceptionMacro("Not implemented");
//      const PixelType& threadMin  = m_ThreadMin [threadId];
//      const PixelType& threadMax  = m_ThreadMax [threadId];

//      for (unsigned int j = 0; j < numberOfComponent; ++j)
//        {
//        if (threadMin[j] < minimum[j])
//          {
//          minimum[j] = threadMin[j];
//          }
//        if (threadMax[j] > maximum[j])
//          {
//          maximum[j] = threadMax[j];
//          }
//        }
      }

    if (m_EnableFirstOrderStats)
      {
      streamFirstOrderAccumulator += m_ThreadFirstOrderAccumulators[threadId];
      }

    if (m_EnableSecondOrderStats)
      {
      streamSecondOrderAccumulator += m_ThreadSecondOrderAccumulators[threadId];
      streamSecondOrderComponentAccumulator += m_ThreadSecondOrderComponentAccumulators[threadId];
      }
    // Ignored Infinite Pixels
    ignoredInfinitePixelCount += m_IgnoredInfinitePixelCount[threadId];
    // Ignored Pixels
    ignoredUserPixelCount += m_IgnoredUserPixelCount[threadId];
    }

  itk::VariableLengthVector<unsigned int> nbRelevantPixels(numberOfComponent);
  nbRelevantPixels.Fill(nbPixels);
  nbRelevantPixels -= ignoredInfinitePixelCount + ignoredUserPixelCount;

  for (int i = 0; i < numberOfComponent; i++)
    {
    if( nbRelevantPixels[i]==0 )
      {
      itkExceptionMacro("Statistics cannot be calculated with zero relevant pixels.");
      }
    }

  // Final calculations
  if (m_EnableMinMax)
    {
    this->GetMinimumOutput()->Set(minimum);
    this->GetMaximumOutput()->Set(maximum);
    }

  if (m_EnableFirstOrderStats)
    {
    RealType componentMean = 0;
    for (int i = 0; i < numberOfComponent; i++)
      {
      componentMean += streamFirstOrderAccumulator[i] / nbRelevantPixels[i];
      }
    componentMean /= numberOfComponent;
    this->GetComponentMeanOutput()->Set(componentMean);

    RealPixelType mean = streamFirstOrderAccumulator;
    for (int i = 0; i < numberOfComponent; i++)
      {
        mean[i] /= nbRelevantPixels[i];
      }
    this->GetMeanOutput()->Set(mean);

    this->GetSumOutput()->Set(streamFirstOrderAccumulator);
    }

  if (m_EnableSecondOrderStats)
    {
    itkExceptionMacro("Not implemented");
//    MatrixType cor = streamSecondOrderAccumulator / nbRelevantPixels;
//    this->GetCorrelationOutput()->Set(cor);

//    const RealPixelType& mean = this->GetMeanOutput()->Get();

//    double regul = 1.0;
//    double regulComponent = 1.0;

//    if( m_UseUnbiasedEstimator && nbRelevantPixels>1 )
//      {
//      regul =
//       static_cast< double >( nbRelevantPixels ) /
//       ( static_cast< double >( nbRelevantPixels ) - 1.0 );
//      }
    
//    if( m_UseUnbiasedEstimator && (nbRelevantPixels * numberOfComponent) > 1 )
//      {
//      regulComponent =
//        static_cast< double >(nbRelevantPixels * numberOfComponent) /
//       ( static_cast< double >(nbRelevantPixels * numberOfComponent) - 1.0 );
//      }

//    MatrixType cov  = cor;
//    for (unsigned int r = 0; r < numberOfComponent; ++r)
//      {
//      for (unsigned int c = 0; c < numberOfComponent; ++c)
//        {
//        cov(r, c) = regul * (cov(r, c) - mean[r] * mean[c]);
//        }
//      }
//    this->GetCovarianceOutput()->Set(cov);

//    this->GetComponentMeanOutput()->Set(streamFirstOrderComponentAccumulator / (nbRelevantPixels * numberOfComponent));
//    this->GetComponentCorrelationOutput()->Set(streamSecondOrderComponentAccumulator / (nbRelevantPixels * numberOfComponent));
//    this->GetComponentCovarianceOutput()->Set(
//        regulComponent * (this->GetComponentCorrelation()
//           - (this->GetComponentMean() * this->GetComponentMean())));
    }
}

template<class TInputImage, class TPrecision>
void
PersistentStreamingStatisticsVectorImageFilterEx<TInputImage, TPrecision>
::ThreadedGenerateData(const RegionType& outputRegionForThread, itk::ThreadIdType threadId)
 {
  // Support progress methods/callbacks
  itk::ProgressReporter progress(this, threadId, outputRegionForThread.GetNumberOfPixels());

  // Grab the input
  InputImagePointer inputPtr = const_cast<TInputImage *>(this->GetInput());
//  PixelType& threadMin  = m_ThreadMin [threadId];
//  PixelType& threadMax  = m_ThreadMax [threadId];


  itk::ImageRegionConstIterator<TInputImage> it(inputPtr, outputRegionForThread);

  int vectorSize = this->GetInput()->GetVectorLength();
  RealPixelType& threadFirstOrder  = m_ThreadFirstOrderAccumulators [threadId];
  for (it.GoToBegin(); !it.IsAtEnd(); ++it, progress.CompletedPixel())
    {
    const PixelType& vectorValue = it.Get();

    for (unsigned int j = 0; j < vectorSize; ++j)
      {
      float value = (float)(vectorValue[j]);
      if (m_IgnoreInfiniteValues && !vnl_math_isfinite(value))
        {
        m_IgnoredInfinitePixelCount[threadId][j] ++;
        }
        else
          {
          if (m_IgnoreUserDefinedValue && value == m_UserIgnoredValue)
            {
              m_IgnoredUserPixelCount[threadId][j] ++;
            }
          else
            {
            if (m_EnableFirstOrderStats)
              {
          //      RealType& threadFirstOrderComponent  = m_ThreadFirstOrderComponentAccumulators [threadId];

              threadFirstOrder[j] += value;

          //      for (unsigned int i = 0; i < vectorValue.GetSize(); ++i)
          //        {
          //        threadFirstOrderComponent += vectorValue[i];
          //        }
              }
            }
          }
      }

//    if (m_EnableMinMax)
//      {
//      for (unsigned int j = 0; j < vectorValue.GetSize(); ++j)
//        {
//        if (vectorValue[j] < threadMin[j])
//          {
//          threadMin[j] = vectorValue[j];
//          }
//        if (vectorValue[j] > threadMax[j])
//          {
//          threadMax[j] = vectorValue[j];
//          }
//        }
//      }


//    if (m_EnableSecondOrderStats)
//      {
//      MatrixType&    threadSecondOrder = m_ThreadSecondOrderAccumulators[threadId];
//      RealType& threadSecondOrderComponent = m_ThreadSecondOrderComponentAccumulators[threadId];

//      for (unsigned int r = 0; r < threadSecondOrder.Rows(); ++r)
//        {
//        for (unsigned int c = 0; c < threadSecondOrder.Cols(); ++c)
//          {
//          threadSecondOrder(r, c) += static_cast<PrecisionType>(vectorValue[r]) * static_cast<PrecisionType>(vectorValue[c]);
//          }
//        }
//      threadSecondOrderComponent += vectorValue.GetSquaredNorm();
//      }
  }
}

template <class TImage, class TPrecision>
void
PersistentStreamingStatisticsVectorImageFilterEx<TImage, TPrecision>
::PrintSelf(std::ostream& os, itk::Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "Min: "         << this->GetMinimumOutput()->Get()     << std::endl;
  os << indent << "Max: "         << this->GetMaximumOutput()->Get()     << std::endl;
  os << indent << "Mean: "        << this->GetMeanOutput()->Get()        << std::endl;
  os << indent << "Covariance: "  << this->GetCovarianceOutput()->Get()  << std::endl;
  os << indent << "Correlation: " << this->GetCorrelationOutput()->Get() << std::endl;
  os << indent << "Component Mean: "        << this->GetComponentMeanOutput()->Get()        << std::endl;
  os << indent << "Component Covariance: "  << this->GetComponentCovarianceOutput()->Get()  << std::endl;
  os << indent << "Component Correlation: " << this->GetComponentCorrelationOutput()->Get() << std::endl;
  os << indent << "UseUnbiasedEstimator: "  << (this->m_UseUnbiasedEstimator ? "true" : "false")  << std::endl;
}

} // end namespace otb
#endif
