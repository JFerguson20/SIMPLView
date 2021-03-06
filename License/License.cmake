# --------------------------------------------------------------------
# create Resource files for the various license files that are used and
# also create a header file that lists all the License Files
set(LICENSE_FILES
                    ${PROJECT_RESOURCES_DIR}/ThirdParty/Eigen.txt
                    ${PROJECT_RESOURCES_DIR}/ThirdParty/HDF5.txt
                    ${PROJECT_RESOURCES_DIR}/ThirdParty/ITK.txt
                    ${PROJECT_RESOURCES_DIR}/ThirdParty/Qt.txt
                    ${PROJECT_RESOURCES_DIR}/ThirdParty/Qwt.txt

           )
set(SIMPLView_LICENSE_FILE ${PROJECT_RESOURCES_DIR}/SIMPLView/SIMPLViewLicense.txt)
set(QRC_LICENSE_FILES "")
set(LICENSE_HEADER_FILE  ${PROJECT_BINARY_DIR}/SIMPLView/License/${PROJECT_NAME}LicenseFiles.h_tmp)
file(WRITE ${LICENSE_HEADER_FILE} "#ifndef _LICENSE_FILES_H_\n")
file(APPEND ${LICENSE_HEADER_FILE} "#define _LICENSE_FILES_H_\n")
file(APPEND ${LICENSE_HEADER_FILE} "namespace ${PROJECT_PREFIX} {\n")
file(APPEND ${LICENSE_HEADER_FILE} "  QStringList LicenseList = (QStringList()  ")

set(THIRDPARTY_QRC_CONTENTS "<!DOCTYPE RCC>\n<RCC version=\"1.0\">\n<qresource>\n")

foreach(lf ${LICENSE_FILES})
  string(CONCAT THIRDPARTY_QRC_CONTENTS ${THIRDPARTY_QRC_CONTENTS} "<file>")
  get_filename_component(cmp_text_file_name ${lf} NAME_WE)

  set(cmp_text_file_name "ThirdParty/${cmp_text_file_name}.txt")
  string(CONCAT THIRDPARTY_QRC_CONTENTS ${THIRDPARTY_QRC_CONTENTS} ${cmp_text_file_name})

  get_filename_component(lf_fn ${lf} NAME_WE)
  # Copy the text file into the Build Directory
  configure_file("${lf}" ${PROJECT_BINARY_DIR}/ThirdParty/${lf_fn}.txt COPYONLY )

  # create the Qt Resource File
  set(CMP_RESOURCE_FILE_NAME ${lf_fn}.txt)
  
  file(APPEND ${LICENSE_HEADER_FILE} " << \":/ThirdParty/${lf_fn}.txt\"")
  string(CONCAT THIRDPARTY_QRC_CONTENTS ${THIRDPARTY_QRC_CONTENTS} "</file>\n")
endforeach(lf ${LICENSE_FILES})

string(CONCAT THIRDPARTY_QRC_CONTENTS ${THIRDPARTY_QRC_CONTENTS} "</qresource>\n</RCC>")
set(cmp_contents "${THIRDPARTY_QRC_CONTENTS}")
configure_file(${CMP_CONFIGURED_FILES_SOURCE_DIR}/QtResourceFile-All.qrc.in
                   ${PROJECT_BINARY_DIR}/ThirdParty.qrc)

set(QRC_LICENSE_FILES ${QRC_LICENSE_FILES} ${PROJECT_BINARY_DIR}/ThirdParty.qrc)

set(cmp_text_file_name "SIMPLView/SIMPLViewLicense.txt")

configure_file("${SIMPLView_LICENSE_FILE}" ${PROJECT_BINARY_DIR}/SIMPLView/SIMPLViewLicense.txt   COPYONLY )


# create the Qt Resource File
# configure_file(${CMP_CONFIGURED_FILES_SOURCE_DIR}/QtResourceFile.qrc.in ${PROJECT_BINARY_DIR}/SIMPLView.qrc)
# set(QRC_LICENSE_FILES ${QRC_LICENSE_FILES} ${PROJECT_BINARY_DIR}/SIMPLView.qrc)

file(APPEND ${LICENSE_HEADER_FILE} " << \":/SIMPLView/SIMPLViewLicense.txt\"")

cmp_IDE_GENERATED_PROPERTIES("Generated/qrc" "${QRC_LICENSE_FILES}" "")

file(APPEND ${LICENSE_HEADER_FILE}  ");\n")
file(APPEND ${LICENSE_HEADER_FILE}  "}\n#endif /* _LICENSE_FILES_H_ */ \n")

cmpReplaceFileIfDifferent(OLD_FILE_PATH ${PROJECT_BINARY_DIR}/SIMPLView/License/${PROJECT_NAME}LicenseFiles.h
                          NEW_FILE_PATH ${LICENSE_HEADER_FILE} )
