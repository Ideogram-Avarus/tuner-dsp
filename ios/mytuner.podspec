require "json"

package = JSON.parse(File.read(File.join(__dir__, "..", "package.json")))

Pod::Spec.new do |s|
  s.name            = "mytuner"
  s.version         = package["version"]
  s.summary         = "DSP Tuner Engine"
  s.description     = "High performance pitch detection engine"
  s.homepage        = "https://github.com/Ideogram-Avarus/tuner-dsp"
  s.license         = "MIT"
  s.platforms       = { :ios => "13.4" }
  s.author          = "Ideogram-Avarus"
  s.source          = { :git => "https://github.com/Ideogram-Avarus/tuner-dsp.git", :tag => "#{s.version}" }

  s.source_files    = "ios/**/*.{h,m,mm}", "shared/**/*.{h,cpp,hpp}"
  s.header_dir      = "mytuner"
  
  s.pod_target_xcconfig = {
    "CLANG_CXX_LANGUAGE_STANDARD" => "c++20",
    "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/shared\" \"$(PODS_TARGET_SRCROOT)/shared/include\""
  }

  install_modules_dependencies(s)
end