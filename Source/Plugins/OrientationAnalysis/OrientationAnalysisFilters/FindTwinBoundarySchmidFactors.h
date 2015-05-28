/* ============================================================================
* Copyright (c) 2009-2015 BlueQuartz Software, LLC
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
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its 
* contributors may be used to endorse or promote products derived from this software 
* without specific prior written permission.
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
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


#ifndef _FindTwinBoundarySchmidFactors_H_
#define _FindTwinBoundarySchmidFactors_H_

#include <vector>
#include <QtCore/QString>

#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/AbstractFilter.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/DataArrays/IDataArray.h"
#include "DREAM3DLib/DataContainers/DataContainer.h"

#include "OrientationLib/SpaceGroupOps/CubicOps.h"
#include "OrientationLib/SpaceGroupOps/HexagonalOps.h"
#include "OrientationLib/SpaceGroupOps/SpaceGroupOps.h"
#include "OrientationLib/SpaceGroupOps/OrthoRhombicOps.h"

/**
 * @class FindTwinBoundarySchmidFactors FindTwinBoundarySchmidFactors.h DREAM3DLib/GenericFilters/FindTwinBoundarySchmidFactors.h
 * @brief
 * @author Michael A Groeber (AFRL)
 * @date Nov 19, 2011
 * @version 1.0
 */
class FindTwinBoundarySchmidFactors : public AbstractFilter
{
    Q_OBJECT /* Need this for Qt's signals and slots mechanism to work */
  public:
    DREAM3D_SHARED_POINTERS(FindTwinBoundarySchmidFactors)
    DREAM3D_STATIC_NEW_MACRO(FindTwinBoundarySchmidFactors)
    DREAM3D_TYPE_MACRO_SUPER(FindTwinBoundarySchmidFactors, AbstractFilter)

    virtual ~FindTwinBoundarySchmidFactors();

    DREAM3D_FILTER_PARAMETER(bool, WriteFile)
    Q_PROPERTY(bool WriteFile READ getWriteFile WRITE setWriteFile)

    DREAM3D_FILTER_PARAMETER(QString, TwinBoundarySchmidFactorsFile)
    Q_PROPERTY(QString TwinBoundarySchmidFactorsFile READ getTwinBoundarySchmidFactorsFile WRITE setTwinBoundarySchmidFactorsFile)

    DREAM3D_FILTER_PARAMETER(FloatVec3_t, LoadingDir)
    Q_PROPERTY(FloatVec3_t LoadingDir READ getLoadingDir WRITE setLoadingDir)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, AvgQuatsArrayPath)
    Q_PROPERTY(DataArrayPath AvgQuatsArrayPath READ getAvgQuatsArrayPath WRITE setAvgQuatsArrayPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, FeaturePhasesArrayPath)
    Q_PROPERTY(DataArrayPath FeaturePhasesArrayPath READ getFeaturePhasesArrayPath WRITE setFeaturePhasesArrayPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, CrystalStructuresArrayPath)
    Q_PROPERTY(DataArrayPath CrystalStructuresArrayPath READ getCrystalStructuresArrayPath WRITE setCrystalStructuresArrayPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, SurfaceMeshFaceLabelsArrayPath)
    Q_PROPERTY(DataArrayPath SurfaceMeshFaceLabelsArrayPath READ getSurfaceMeshFaceLabelsArrayPath WRITE setSurfaceMeshFaceLabelsArrayPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, SurfaceMeshFaceNormalsArrayPath)
    Q_PROPERTY(DataArrayPath SurfaceMeshFaceNormalsArrayPath READ getSurfaceMeshFaceNormalsArrayPath WRITE setSurfaceMeshFaceNormalsArrayPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, SurfaceMeshTwinBoundaryArrayPath)
    Q_PROPERTY(DataArrayPath SurfaceMeshTwinBoundaryArrayPath READ getSurfaceMeshTwinBoundaryArrayPath WRITE setSurfaceMeshTwinBoundaryArrayPath)

    DREAM3D_FILTER_PARAMETER(QString, SurfaceMeshTwinBoundarySchmidFactorsArrayName)
    Q_PROPERTY(QString SurfaceMeshTwinBoundarySchmidFactorsArrayName READ getSurfaceMeshTwinBoundarySchmidFactorsArrayName WRITE setSurfaceMeshTwinBoundarySchmidFactorsArrayName)

    virtual const QString getCompiledLibraryName();
    virtual AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters);
    virtual const QString getGroupName();
    virtual const QString getSubGroupName();
    virtual const QString getHumanLabel();

    virtual void setupFilterParameters();
    /**
    * @brief This method will write the options to a file
    * @param writer The writer that is used to write the options to a file
    */
    virtual int writeFilterParameters(AbstractFilterParametersWriter* writer, int index);

    /**
    * @brief This method will read the options from a file
    * @param reader The reader that is used to read the options from a file
    */
    virtual void readFilterParameters(AbstractFilterParametersReader* reader, int index);

    /**
     * @brief Reimplemented from @see AbstractFilter class
     */
    virtual void execute();
    virtual void preflight();

  signals:
    void updateFilterParameters(AbstractFilter* filter);
    void parametersChanged();
    void preflightAboutToExecute();
    void preflightExecuted();

  protected:
    FindTwinBoundarySchmidFactors();

  private:
    QVector<SpaceGroupOps::Pointer> m_OrientationOps;
    CubicOps::Pointer m_CubicOps;
    HexagonalOps::Pointer m_HexOps;
    OrthoRhombicOps::Pointer m_OrthoOps;

    DEFINE_REQUIRED_DATAARRAY_VARIABLE(float, AvgQuats)
    DEFINE_REQUIRED_DATAARRAY_VARIABLE(int32_t, FeaturePhases)
    DEFINE_REQUIRED_DATAARRAY_VARIABLE(unsigned int, CrystalStructures)
    DEFINE_REQUIRED_DATAARRAY_VARIABLE(int32_t, SurfaceMeshFaceLabels)
    DEFINE_REQUIRED_DATAARRAY_VARIABLE(double, SurfaceMeshFaceNormals)
    DEFINE_REQUIRED_DATAARRAY_VARIABLE(bool, SurfaceMeshTwinBoundary)
    DEFINE_CREATED_DATAARRAY_VARIABLE(float, SurfaceMeshTwinBoundarySchmidFactors)

    void dataCheckVoxel();
    void dataCheckSurfaceMesh();

    FindTwinBoundarySchmidFactors(const FindTwinBoundarySchmidFactors&); // Copy Constructor Not Implemented
    void operator=(const FindTwinBoundarySchmidFactors&); // Operator '=' Not Implemented
};

#endif /* FindTwinBoundarySchmidFactors_H_ */

