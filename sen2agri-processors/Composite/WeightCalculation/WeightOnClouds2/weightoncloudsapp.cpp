
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
#include "otbWrapperApplication.h"
#include "otbWrapperApplicationFactory.h"

#include "cloudmaskbinarization.h"
#include "cloudsinterpolation.h"
#include "gaussianfilter.h"
#include "cloudweightcomputation.h"
#include "paddingimagehandler.h"
#include "MetadataHelperFactory.h"

namespace otb
{

namespace Wrapper
{

class WeightOnClouds2 : public Application
{

public:
  /** Standard class typedefs. */
  typedef WeightOnClouds2                      Self;
  typedef Application                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Standard macro */
  itkNewMacro(Self);

  itkTypeMacro(WeightOnClouds2, otb::Application);

private:
  void DoInit()
  {
    SetName("WeightOnClouds2");
    SetDescription("Computes the cloud weight value for the given mask cloud and parameters");

    SetDocName("Weight on Clouds");
    SetDocLongDescription("This application implements the Weight On Clouds algorithm for the Composite Processor");

    SetDocLimitations("None");
    SetDocAuthors("CIU");
    SetDocSeeAlso(" ");
    AddDocTag("Util");

    AddParameter(ParameterType_String,  "inxml",   "Input xml file");
    SetParameterDescription("inxml", "Input XML file.");

    AddParameter(ParameterType_String,  "incldmsk",   "Input cloud mask image");
    SetParameterDescription("incldmsk", "Image containing the cloud mask.");

    AddParameter(ParameterType_Int, "incldmskres", "Input cloud mask resolution");
    SetParameterDescription("incldmskres", "The resolution of the input cloud mask image. It is optional and if not set, then the resolution from the input file will be used");
    SetDefaultParameterInt("incldmskres", -1);
    MandatoryOff("incldmskres");

    AddParameter(ParameterType_Int, "coarseres", "Coarse resolution");
    SetParameterDescription("coarseres", "The resolution for the undersampling.");
    SetDefaultParameterInt("coarseres", 240);
    MandatoryOff("coarseres");

    AddParameter(ParameterType_Float, "sigmasmallcld", "Small cloud sigma");
    SetParameterDescription("sigmasmallcld", "Sigma value for the small cloud gaussian filter.");

    AddParameter(ParameterType_Float, "sigmalargecld", "Large cloud sigma");
    SetParameterDescription("sigmalargecld", "Sigma value for the large cloud gaussian filter.");

    AddParameter(ParameterType_Int, "kernelwidth", "Gaussian filter kernel width");
    SetParameterDescription("kernelwidth", "The gaussian filter kernel width.");
    SetDefaultParameterInt("kernelwidth", 801);
    MandatoryOff("kernelwidth");

    AddParameter(ParameterType_Int, "outres", "Resolution of the output image");
    SetParameterDescription("outres", "The resolution at which the output will be produced.");
    SetDefaultParameterInt("outres", -1);
    MandatoryOff("outres");

    AddParameter(ParameterType_OutputImage, "out", "Output Cloud Weight Image");
    SetParameterDescription("out","The output image containg the computed cloud weight for each pixel.");

    // Doc example parameter settings
    SetDocExampleParameterValue("incldmsk", "verySmallFSATSW_r.tif");
    SetDocExampleParameterValue("incldmskres", "20");
    SetDocExampleParameterValue("coarseres", "240");
    SetDocExampleParameterValue("sigmasmallcld", "10.0");
    SetDocExampleParameterValue("sigmalargecld", "50.0");
    SetDocExampleParameterValue("kernelwidth", "81");
    SetDocExampleParameterValue("outres", "10");
    SetDocExampleParameterValue("out", "apAOTWeightOutput.tif");
  }

  void DoUpdateParameters()
  {
  }

  void DoExecute()
  {
    // Get the input image list
    std::string inCldFileName = GetParameterString("incldmsk");
    if (inCldFileName.empty())
    {
        itkExceptionMacro("No input Image set...; please set the input image");
    }
    int inputCloudMaskResolution = GetParameterInt("incldmskres");
    int coarseResolution = GetParameterInt("coarseres");
    float sigmaSmallCloud = GetParameterFloat("sigmasmallcld");
    float sigmaLargeCloud = GetParameterFloat("sigmalargecld");
    int outputResolution = GetParameterInt("outres");
    int gaussianKernelWidth = GetParameterInt("kernelwidth");

    std::cout << "=================================" << std::endl;
    std::cout << "sigmasmallcld : " << sigmaSmallCloud << std::endl;
    std::cout << "sigmalargecld : " << sigmaLargeCloud << std::endl;
    std::cout << "=================================" << std::endl;

    long inImageWidth, inImageHeight;

    m_underSampler.SetOutputResolution(coarseResolution);

    bool test = 0;
    if(test) {
        std::string inXml = GetParameterAsString("inxml");
        auto factory = MetadataHelperFactory::New();
        auto pHelper = factory->GetMetadataHelper(inXml);
        std::string cldFileName = pHelper->GetCloudImageFileName();
        itkWarningMacro(<< "Cld file name: " << cldFileName);

        m_underSampler.SetInputFileName(cldFileName);
        //m_underSampler.SetInterpolator(Interpolator_Linear);
        //m_underSampler.SetInterpolator(Interpolator_NNeighbor);
        m_cloudMaskBinarization.SetInputImageReader(m_underSampler.GetOutputImageSource());
        // Compute the DistLargeCloud, Low Res
        m_gaussianFilterSmallCloud.SetInputImageReader(m_cloudMaskBinarization.GetOutputImageSource());
        m_gaussianFilterLargeCloud.SetInputImageReader(m_cloudMaskBinarization.GetOutputImageSource());
    } else {
        m_cloudMaskBinarization.SetInputFileName(inCldFileName);
        m_underSampler.SetInputImageReader(m_cloudMaskBinarization.GetOutputImageSource());
        // Compute the DistLargeCloud, Low Res
        m_gaussianFilterSmallCloud.SetInputImageReader(m_underSampler.GetOutputImageSource());
        m_gaussianFilterLargeCloud.SetInputImageReader(m_underSampler.GetOutputImageSource());
    }

    m_underSampler.SetInputResolution(inputCloudMaskResolution);
    if(inputCloudMaskResolution == -1) {
        inputCloudMaskResolution = m_underSampler.GetInputImageResolution();
    }
    m_underSampler.GetInputImageDimension(inImageWidth, inImageHeight);

    // Check if the image size differ

    m_gaussianFilterSmallCloud.SetSigma(sigmaSmallCloud);
    m_gaussianFilterSmallCloud.SetKernelWidth(gaussianKernelWidth);

    m_gaussianFilterLargeCloud.SetSigma(sigmaLargeCloud);
    m_gaussianFilterLargeCloud.SetKernelWidth(gaussianKernelWidth);

    if(outputResolution < 0) {
        outputResolution = inputCloudMaskResolution;
    }

    // resample at the current small resolution (10 or 20) the small cloud large resolution image
    m_overSamplerSmallCloud.SetInputImageReader(m_gaussianFilterSmallCloud.GetOutputImageSource());
    m_overSamplerSmallCloud.SetInputResolution(coarseResolution);
    m_overSamplerSmallCloud.SetOutputResolution(outputResolution);
    m_overSamplerSmallCloud.SetInterpolator(Interpolator_Linear);
    m_overSamplerSmallCloud.SetOutputForcedSize(inImageWidth, inImageHeight);

    // resample at the current small resolution (10 or 20) the large cloud large resolution image
    m_overSamplerLargeCloud.SetInputImageReader(m_gaussianFilterLargeCloud.GetOutputImageSource());
    m_overSamplerLargeCloud.SetInputResolution(coarseResolution);
    m_overSamplerLargeCloud.SetOutputResolution(outputResolution);
    m_overSamplerLargeCloud.SetInterpolator(Interpolator_Linear);
    m_overSamplerLargeCloud.SetOutputForcedSize(inImageWidth, inImageHeight);

    // compute the weight on clouds
    m_cloudWeightComputation.SetInputImageReader1(m_overSamplerSmallCloud.GetOutputImageSource());
    m_cloudWeightComputation.SetInputImageReader2(m_overSamplerLargeCloud.GetOutputImageSource());

    // Set the output image
    SetParameterOutputImage("out", m_cloudWeightComputation.GetOutputImageSource()->GetOutput());

    // write debug infos if needed
    if(1) {
        std::string strOutImg = GetParameterAsString("out");
        std::string strBaseName = strOutImg;
        size_t lastDotIdx = strOutImg.find_last_of(".");
        if(lastDotIdx != std::string::npos) {
            strBaseName = strOutImg.substr(0, lastDotIdx);
        }

        std::string coarseResStr = std::to_string(coarseResolution);
        std::string inputResStr = std::to_string(inputCloudMaskResolution);

        std::string binarizedFile = strBaseName +
                (test ? "_binarized_clouds_" + coarseResStr + "m.tif" :
                        "_1_binarized_clouds_" + inputResStr + "m.tif");
        m_cloudMaskBinarization.SetOutputFileName(binarizedFile);
        m_cloudMaskBinarization.WriteToOutputFile();

        std::string undersamplerFile = strBaseName + "_2_bco_clouds_" + coarseResStr + "m.tif";
        m_underSampler.SetOutputFileName(undersamplerFile);
        m_underSampler.WriteToOutputFile();

        std::string smallCldLowRes = strBaseName + "_3_small_cloud_" + coarseResStr + "m.tif";
        m_gaussianFilterSmallCloud.SetOutputFileName(smallCldLowRes);
        m_gaussianFilterSmallCloud.WriteToOutputFile();

        std::string largeCldLowRes = strBaseName + "_4_large_cloud_" + coarseResStr + "m.tif";
        m_gaussianFilterLargeCloud.SetOutputFileName(largeCldLowRes);
        m_gaussianFilterLargeCloud.WriteToOutputFile();

        std::string smallCldHighRes = strBaseName + "_5_small_cloud_" + inputResStr + "m.tif";
        m_overSamplerSmallCloud.SetOutputFileName(smallCldHighRes);
        m_overSamplerSmallCloud.WriteToOutputFile();

        std::string largeCldHighRes = strBaseName + "_6_large_cloud_" + inputResStr + "m.tif";
        m_overSamplerLargeCloud.SetOutputFileName(largeCldHighRes);
        m_overSamplerLargeCloud.WriteToOutputFile();
    }
  }

  CloudsInterpolation<otb::Wrapper::FloatImageType, otb::Wrapper::FloatImageType> m_underSampler;
  CloudMaskBinarization<otb::Wrapper::FloatImageType, otb::Wrapper::FloatImageType> m_cloudMaskBinarization;
  GaussianFilter<otb::Wrapper::FloatImageType, otb::Wrapper::FloatImageType> m_gaussianFilterSmallCloud;
  GaussianFilter<otb::Wrapper::FloatImageType, otb::Wrapper::FloatImageType> m_gaussianFilterLargeCloud;
  CloudsInterpolation<otb::Wrapper::FloatImageType, otb::Wrapper::FloatImageType> m_overSamplerSmallCloud;
  CloudsInterpolation<otb::Wrapper::FloatImageType, otb::Wrapper::FloatImageType> m_overSamplerLargeCloud;
  CloudWeightComputation m_cloudWeightComputation;
};

} // namespace Wrapper
} // namespace otb

OTB_APPLICATION_EXPORT(otb::Wrapper::WeightOnClouds2)

