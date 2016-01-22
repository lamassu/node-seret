{
  "targets": [{
    "target_name": "seret",
    "sources": ["./src/camera.c", "./src/seret.cc"],
    "cflags": ["-m64", "-Wall", "-Wextra", "-pedantic", "-ftrapv"],
    "cflags_c": ["-std=c11", "-Wno-unused-parameter"],
    "cflags_cc": ["-std=c++11"],
    "libraries": ["/opt/libjpeg-turbo/lib64/libturbojpeg.a"],
    "include_dirs" : ["/opt/libjpeg-turbo/include/"]
  }]
}

