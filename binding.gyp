{
    "targets" : [
        {
            "target_name" : "shm",
            "sources" : [
                "src/binding.cc",
                "src/shm.cc"
            ],
            'cflags!' : ['-fno-exceptions'],
            'cflags_cc!' : ['-fno-exceptions'],
            'include_dirs' : [
                "<!@(node -p \"require('node-addon-api').include\")",
		        "<(module_root_dir)/deps/simdb"
            ],
            'dependencies' : [
                "<!(node -p \"require('node-addon-api').gyp\")"            ],
            'conditions' : [
                [ 'OS=="win"', {
                    "msvs_settings" : {
                        "VCCLCompilerTool" : {
                            "ExceptionHandling" : 1
                        }
                    }
                }],
                [ 'OS=="mac"', {
                    "xcode_settings": {
                        "CLANG_CXX_LANGUAGE_STANDARD": "c++11",
                        "CLANG_CXX_LIBRARY" : "libc++",
                        "GCC_ENABLE_CPP_EXCEPTIONS" : "YES",
                        "MACOSX_DEPLOYMENT_TARGET" : "10.7"
                    }
                }]
            ]
        }
    ]
}
