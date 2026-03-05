module.exports = {
  dependency: {
    platforms: {
      android: {
        cmakeListsPath: './android/CMakeLists.txt', 
        packageImportPath: 'import com.tunerdsp.TunerModulePackage;',
        packageInstance: 'new TunerModulePackage()',
      },
      ios: {},
    },
  },
};