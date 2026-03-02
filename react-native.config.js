



module.exports = {
  dependency: {
    platforms: {
      android: {
        sourceDir: './android',
        cmakeListsPath: 'import com.mytuner.TunerPackage;',
        packageInstance: 'new TunerPackage()'
      },
      ios: {
        pdspecPath: './ios/mytuner.podspec',
      },
    },
  },
};