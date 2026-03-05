module.exports = {
  dependency: {
    platforms: {
      android: {
        cmakeListsPath: './android/CMakeLists.txt',  // optional, but good
        packageImportPath: 'import com.tunerdsp.TunerModulePackage;',
        packageInstance: 'new TunerModulePackage()',
      },
      ios: {}, // if you add iOS later
    },
  },
};