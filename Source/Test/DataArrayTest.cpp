/* ============================================================================
 * Copyright (c) 2011, Michael A. Jackson (BlueQuartz Software)
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
 * Neither the name of Michael A. Jackson nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
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
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


#include <stdlib.h>

#include <iostream>
#include <string>

#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/DataArray.hpp"


#include "UnitTestSupport.hpp"

#include "TestFileLocations.h"

#define NUM_ELEMENTS  10
#define NUM_COMPONENTS 2
#define NUM_TUPLES     5

#define NUM_ELEMENTS_2   20
#define NUM_COMPONENTS_2 2
#define NUM_TUPLES_2     10

#define NUM_ELEMENTS_3   16
#define NUM_COMPONENTS_3 2
#define NUM_TUPLES_3     8

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void RemoveTestFiles()
{
#if REMOVE_TEST_FILES

#endif
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void TestDataArray()
{
  Int32ArrayType::Pointer int32Array = Int32ArrayType::CreateArray(NUM_ELEMENTS);

  DREAM3D_REQUIRE_EQUAL(NUM_ELEMENTS , int32Array->GetNumberOfTuples());
  DREAM3D_REQUIRE_EQUAL(NUM_ELEMENTS , int32Array->GetSize());
  int32Array->SetNumberOfComponents(NUM_COMPONENTS);
  DREAM3D_REQUIRE_EQUAL(NUM_TUPLES , int32Array->GetNumberOfTuples());
  DREAM3D_REQUIRE_EQUAL(NUM_ELEMENTS , int32Array->GetSize());

  // Resize Larger
  int32Array->Resize(NUM_TUPLES_2);
  DREAM3D_REQUIRE_EQUAL(NUM_TUPLES_2 , int32Array->GetNumberOfTuples());
  DREAM3D_REQUIRE_EQUAL(NUM_ELEMENTS_2 , int32Array->GetSize());


  // Resize Smaller
  int32Array->Resize(NUM_TUPLES_3);
  DREAM3D_REQUIRE_EQUAL(NUM_TUPLES_3 , int32Array->GetNumberOfTuples());
  DREAM3D_REQUIRE_EQUAL(NUM_ELEMENTS_3 , int32Array->GetSize());

}

// -----------------------------------------------------------------------------
//  Use unit test framework
// -----------------------------------------------------------------------------
int main(int argc, char **argv)
{
  int err = EXIT_SUCCESS;
  DREAM3D_REGISTER_TEST( TestDataArray() );


  PRINT_TEST_SUMMARY();
  return err;
}

