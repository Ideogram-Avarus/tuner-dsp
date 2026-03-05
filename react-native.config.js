module.exports = {
  dependency: {
    platforms: {
      android: {
        cmakeListsPath: './CMakeLists.txt', 
        packageImportPath: 'import com.tunerdsp.TunerDspModulePackage;',
        packageInstance: 'new TunerDspModulePackage()',
      },
      ios: {},
    },
  },
};