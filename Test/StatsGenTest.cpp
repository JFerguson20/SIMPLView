/* ============================================================================
 * Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2010, Dr. Michael A. Groeber (US Air Force Research Laboratories
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Michael A. Groeber, Michael A. Jackson, the US Air Force,
 * BlueQuartz Software nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  This code was written under United States Air Force Contract number
 *                           FA8650-07-D-5800
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream>
#include <vector>
#include <string>
#include <map>


#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/StatsGen.hpp"


#include "UnitTestSupport.hpp"

void GenHexMDFPlotData()
{

  int err = 0;
  int size = 2500;
  std::vector<float> e1s;
  std::vector<float> e2s;
  std::vector<float> e3s;
  std::vector<float> weights;
  std::vector<float> sigmas;
  std::vector<float> odf;

  odf.resize(HexagonalOps::k_OdfSize);
  Texture::CalculateHexODFData( &(e1s.front()), &(e2s.front()), &(e3s.front()), &(weights.front()), &(sigmas.front()), true, &(odf.front()), e1s.size());


  // These are the input vectors
  std::vector<float> angles;
  std::vector<float> axes;


  // Allocate a new vector to hold the mdf data
  std::vector<float> mdf(HexagonalOps::k_MdfSize);
  // Calculate the MDF Data using the ODF data and the rows from the MDF Table model
  Texture::CalculateMDFData<float, HexagonalOps>(angles.data(), axes.data(), weights.data(), odf.data(), mdf.data(), angles.size());

  size = 20;
  // Now generate the actual XY point data that gets plotted.
  // These are the output vectors
  std::vector<float> x(size);
  std::vector<float> y(size);
  err = StatsGen::GenHexMDFPlotData( &(mdf.front()), &(x.front()), &(y.front()), size );

  DREAM3D_REQUIRE(err >= 0)
}



/**
 * @brief This code is just here to make sure each of the methods in the StatsGen
 *  class gets compiled due to some compilers NOT compiling the templates unless
 *  they are explicitly instantiated.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv)
{
  int err = EXIT_SUCCESS;
  DREAM3D_REGISTER_TEST(GenHexMDFPlotData())

  PRINT_TEST_SUMMARY();
  //return err;
#if 1



  float alpha = 1.0;
  float beta = 1.0;

  std::vector<float> x;
  std::vector<float> y;
  int size = 1000;
  err = StatsGen::GenBetaPlotData(alpha, beta, x, y, size);


  float avg = 1.0f;
  float stdDev = 0.5f;
  err = StatsGen::GenLogNormalPlotData(avg, stdDev, x, y, size);

  float k = 1.4f;
  err = StatsGen::GenPowerLawPlotData(alpha, k, beta, x, y, size);


  float mu = 1.0f;
  float sigma = 1.0f;
  float cutoff = 4.0f;
  float maxCutOff = 4.0f;
  float binstep = 0.75f;
  float max, min;

  err = StatsGen::ComputeNumberOfBins(mu, sigma, cutoff, maxCutOff, binstep, max, min);
  size_t npoints = 1000;

  std::vector<float> binsizes;
  err = StatsGen::GenCutOff(mu, sigma, cutoff, maxCutOff, binstep, x, y, max, size, binsizes);

  {
  std::vector<float> odf(CubicOps::k_OdfSize);

  std::vector<float > x001(npoints * 3);
  std::vector<float > y001(npoints * 3);
  std::vector<float > x011(npoints * 6);
  std::vector<float > y011(npoints * 6);
  std::vector<float > x111(npoints * 4);
  std::vector<float > y111(npoints * 4);
  err = StatsGen::GenCubicODFPlotData(&(odf.front()), &(x001.front()), &(y001.front()), &(x011.front()),
                                     &(y011.front()), &(x111.front()), &(y111.front()), npoints);
  }

  {
  std::vector<float> odf(HexagonalOps::k_OdfSize);

  std::vector<float > x001(npoints * 1);
  std::vector<float > y001(npoints * 1);
  std::vector<float > x011(npoints * 3);
  std::vector<float > y011(npoints * 3);
  std::vector<float > x111(npoints * 3);
  std::vector<float > y111(npoints * 3);
  err = StatsGen::GenHexODFPlotData(&(odf.front()), &(x001.front()), &(y001.front()), &(x011.front()),
                                     &(y011.front()), &(x111.front()), &(y111.front()), npoints);

  }

{
  std::vector<float> odf(OrthoRhombicOps::k_OdfSize);

  std::vector<float > x001(npoints * 3);
  std::vector<float > y001(npoints * 3);
  std::vector<float > x011(npoints * 6);
  std::vector<float > y011(npoints * 6);
  std::vector<float > x111(npoints * 4);
  std::vector<float > y111(npoints * 4);
  err = StatsGen::GenOrthoRhombicODFPlotData(&(odf.front()), &(x001.front()), &(y001.front()), &(x011.front()),
                                     &(y011.front()), &(x111.front()), &(y111.front()), npoints);
}

{
  std::vector<float> odf(OrthoRhombicOps::k_OdfSize);

  std::vector<float > x001(npoints * 1);
  std::vector<float > y001(npoints * 1);
  std::vector<float > x011(npoints * 1);
  std::vector<float > y011(npoints * 1);
  std::vector<float > x111(npoints * 1);
  std::vector<float > y111(npoints * 1);
  err = StatsGen::GenAxisODFPlotData(&(odf.front()), &(x001.front()), &(y001.front()), &(x011.front()),
                                     &(y011.front()), &(x111.front()), &(y111.front()), npoints);
}

  std::vector<float> mdf;

  mdf.resize(CubicOps::k_MdfSize);
  npoints = 13;
  x.resize(npoints);
  y.resize(npoints);
  err = StatsGen::GenCubicMDFPlotData( &(mdf.front()), &(x.front()), &(y.front()), npoints );

  mdf.resize(HexagonalOps::k_MdfSize);
  npoints = 20;
  x.resize(npoints);
  y.resize(npoints);
  err = StatsGen::GenHexMDFPlotData( &(mdf.front()), &(x.front()), &(y.front()), npoints );

  return EXIT_SUCCESS;
#endif
}
