/* ============================================================================
* Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
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

#ifndef OIMImportPlugin_H_
#define OIMImportPlugin_H_

#include <QtCore/QObject>
#include <QtCore/QSettings>
#include "QtSupport/DREAM3DPluginInterface.h"

class OIMImportWidget;
class AIMPluginFrame;


DREAM3D_PLUGIN_CONSTANTS(OIMImport, OIM Import)


class OIMImportPlugin : public QObject, public DREAM3DPluginInterface
{
    Q_OBJECT;
    Q_INTERFACES(DREAM3DPluginInterface)

  public:
    OIMImportPlugin();
    virtual ~OIMImportPlugin();

    QString getPluginName();

    virtual QWidget* getInputWidget(QWidget* parent);
    virtual AIMPluginFrame* getPluginFrame(QWidget* parent);


    virtual void writeSettings(QSettings &prefs);
    virtual void readSettings(QSettings &prefs);
    virtual QIcon icon();
    virtual QUrl htmlHelpIndexFile();

  public slots:
    virtual void displayHelp();

  signals:
    void showHelp(QUrl);


  protected:
    OIMImportWidget* m_InputWidget;

  private:
    OIMImportPlugin(const OIMImportPlugin&); // Copy Constructor Not Implemented
    void operator=(const OIMImportPlugin&); // Operator '=' Not Implemented
};

#endif /* OIMImportPlugin_H_ */
