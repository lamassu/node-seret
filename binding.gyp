{
  "targets": [{
    "target_name": "seret",
    "sources": ["./src/camera.c", "./src/seret.cc"],
    "cflags": ["-m32", "-Wall", "-Wextra", "-pedantic", "-ftrapv"],
    "cflags_c": ["-std=c11", "-Wno-unused-parameter"],
    "cflags_cc": ["-std=c++11"],
    "libraries: ["/opt/libjpeg-turbo/lib64/libturbojpeg.a"],
    "include_dirs" : ["<!(node -e \"require('nan')\")", 
                      "/usr/include/x86_64-linux-gnu",
                      "/opt/libjpeg-turbo/include/"]
  }]
}

