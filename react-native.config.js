module.exports = {
  dependency: {
    platforms: {
      android: {
        cmakeListsPath: './android/CMakeLists.txt', 
        packageImportPath: 'import com.tunerdsp.TunerDspModulePackage;',
        packageInstance: 'new TunerDspModulePackage()',
      },
      ios: {},
    },
  },
};