#
# Be sure to run `pod lib lint JSPLayerSDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'js_player_sdk'
  s.version          = "2.3.34"
  s.summary          = 'JSPlayerSDK.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
JSPlayerSDK for JS live platform.
                       DESC

  s.homepage         = 'https://github.com/ssddawei/JSPlayerSDK'

  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'ssddawei' => '/' }
  s.source           = { :git => 'https://github.com/ssddawei/JSPlayerSDK.git', :tag => s.version.to_s }

  s.platform         = :ios
  s.ios.deployment_target = '8.0'
  # s.pod_target_xcconfig = { 'OTHER_LDFLAGS' => '-lObjC','DEFINES_MODULE' => 'YES', 'VALID_ARCHS[sdk=iphonesimulator*]' => 'x86_64 i386' }
  # s.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64','OTHER_LDFLAGS' => '-lObjC','DEFINES_MODULE' => 'YES', 'VALID_ARCHS[sdk=iphonesimulator*]' => '' }
  s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  s.ios.vendored_frameworks = 'SDK/JSPlayerSDK.framework'
  s.resources = 'SDK/JSPlayerSDKUI.bundle'

end
