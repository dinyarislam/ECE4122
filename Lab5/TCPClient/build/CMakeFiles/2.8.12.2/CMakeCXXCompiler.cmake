set(CMAKE_CXX_COMPILER "/usr/local/pace-apps/spack/packages/0.13/linux-rhel7-cascadelake/intel-19.0.5/mvapich2-2.3.2-hpgbkqoytbjh35qn2t63rdorepxcezek/bin/mpicxx")
set(CMAKE_CXX_COMPILER_ARG1 "")
set(CMAKE_CXX_COMPILER_ID "Intel")
set(CMAKE_CXX_COMPILER_VERSION "19.0.0.20190815")
set(CMAKE_CXX_PLATFORM_ID "Linux")

set(CMAKE_AR "/usr/bin/ar")
set(CMAKE_RANLIB "/usr/bin/ranlib")
set(CMAKE_LINKER "/usr/local/pace-apps/manual/packages/xalt/2.8.4/bin/ld")
set(CMAKE_COMPILER_IS_GNUCXX )
set(CMAKE_CXX_COMPILER_LOADED 1)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_CXX_ABI_COMPILED TRUE)
set(CMAKE_COMPILER_IS_MINGW )
set(CMAKE_COMPILER_IS_CYGWIN )
if(CMAKE_COMPILER_IS_CYGWIN)
  set(CYGWIN 1)
  set(UNIX 1)
endif()

set(CMAKE_CXX_COMPILER_ENV_VAR "CXX")

if(CMAKE_COMPILER_IS_MINGW)
  set(MINGW 1)
endif()
set(CMAKE_CXX_COMPILER_ID_RUN 1)
set(CMAKE_CXX_IGNORE_EXTENSIONS inl;h;hpp;HPP;H;o;O;obj;OBJ;def;DEF;rc;RC)
set(CMAKE_CXX_SOURCE_FILE_EXTENSIONS C;M;c++;cc;cpp;cxx;m;mm;CPP)
set(CMAKE_CXX_LINKER_PREFERENCE 30)
set(CMAKE_CXX_LINKER_PREFERENCE_PROPAGATES 1)

# Save compiler ABI information.
set(CMAKE_CXX_SIZEOF_DATA_PTR "8")
set(CMAKE_CXX_COMPILER_ABI "ELF")
set(CMAKE_CXX_LIBRARY_ARCHITECTURE "")

if(CMAKE_CXX_SIZEOF_DATA_PTR)
  set(CMAKE_SIZEOF_VOID_P "${CMAKE_CXX_SIZEOF_DATA_PTR}")
endif()

if(CMAKE_CXX_COMPILER_ABI)
  set(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_CXX_COMPILER_ABI}")
endif()

if(CMAKE_CXX_LIBRARY_ARCHITECTURE)
  set(CMAKE_LIBRARY_ARCHITECTURE "")
endif()




set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "mpicxx;mpi;imf;svml;irng;stdc++;m;ipgo;decimal;cilkrts;stdc++;irc;svml;c;irc_s;dl;c")
set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "/usr/local/pace-apps/spack/packages/0.13/linux-rhel7-cascadelake/intel-19.0.5/mvapich2-2.3.2-hpgbkqoytbjh35qn2t63rdorepxcezek/lib;/usr/local/pace-apps/spack/packages/0.12/linux-rhel7-x86_64/gcc-4.8.5/gcc-8.3.0-opnwtdjumg2hxo4ljvnx77ugb6afmvj3/lib64;/usr/local/pace-apps/spack/packages/0.13/linux-rhel7-x86_64/gcc-4.8.5/intel-parallel-studio-cluster.2019.5-rde2uvgb2mq2x6obqaklxppmycfngjgm/clck/2019.5/lib/intel64;/usr/local/pace-apps/spack/packages/0.13/linux-rhel7-x86_64/gcc-4.8.5/intel-parallel-studio-cluster.2019.5-rde2uvgb2mq2x6obqaklxppmycfngjgm/compilers_and_libraries_2019.5.281/linux/mpi/intel64/libfabric/lib;/usr/local/pace-apps/spack/packages/0.13/linux-rhel7-x86_64/gcc-4.8.5/intel-parallel-studio-cluster.2019.5-rde2uvgb2mq2x6obqaklxppmycfngjgm/compilers_and_libraries_2019.5.281/linux/ipp/lib/intel64;/usr/local/pace-apps/spack/packages/0.13/linux-rhel7-x86_64/gcc-4.8.5/intel-parallel-studio-cluster.2019.5-rde2uvgb2mq2x6obqaklxppmycfngjgm/compilers_and_libraries_2019.5.281/linux/compiler/lib/intel64_lin;/usr/local/pace-apps/spack/packages/0.13/linux-rhel7-x86_64/gcc-4.8.5/intel-parallel-studio-cluster.2019.5-rde2uvgb2mq2x6obqaklxppmycfngjgm/compilers_and_libraries_2019.5.281/linux/mkl/lib/intel64_lin;/usr/local/pace-apps/spack/packages/0.13/linux-rhel7-x86_64/gcc-4.8.5/intel-parallel-studio-cluster.2019.5-rde2uvgb2mq2x6obqaklxppmycfngjgm/compilers_and_libraries_2019.5.281/linux/tbb/lib/intel64/gcc4.7;/usr/local/pace-apps/spack/packages/0.13/linux-rhel7-x86_64/gcc-4.8.5/intel-parallel-studio-cluster.2019.5-rde2uvgb2mq2x6obqaklxppmycfngjgm/compilers_and_libraries_2019.5.281/linux/daal/lib/intel64_lin;/usr/local/pace-apps/spack/packages/0.13/linux-rhel7-x86_64/gcc-4.8.5/intel-parallel-studio-cluster.2019.5-rde2uvgb2mq2x6obqaklxppmycfngjgm/compilers_and_libraries_2019.5.281/linux/tbb/lib/intel64_lin/gcc4.4;/usr/local/pace-apps/spack/packages/0.13/linux-rhel7-x86_64/gcc-4.8.5/intel-parallel-studio-cluster.2019.5-rde2uvgb2mq2x6obqaklxppmycfngjgm/lib;/storage/pace-apps/spack/packages/0.13/linux-rhel7-x86_64/gcc-4.8.5/intel-parallel-studio-cluster.2019.5-rde2uvgb2mq2x6obqaklxppmycfngjgm/compilers_and_libraries_2019.5.281/linux/compiler/lib/intel64_lin;/storage/pace-apps/spack/packages/0.12/linux-rhel7-x86_64/gcc-4.8.5/gcc-8.3.0-opnwtdjumg2hxo4ljvnx77ugb6afmvj3/lib/gcc/x86_64-pc-linux-gnu/8.3.0;/storage/pace-apps/spack/packages/0.12/linux-rhel7-x86_64/gcc-4.8.5/gcc-8.3.0-opnwtdjumg2hxo4ljvnx77ugb6afmvj3/lib/gcc;/storage/pace-apps/spack/packages/0.12/linux-rhel7-x86_64/gcc-4.8.5/gcc-8.3.0-opnwtdjumg2hxo4ljvnx77ugb6afmvj3/lib64;/lib64;/usr/lib64;/storage/pace-apps/spack/packages/0.12/linux-rhel7-x86_64/gcc-4.8.5/gcc-8.3.0-opnwtdjumg2hxo4ljvnx77ugb6afmvj3/lib;/lib;/usr/lib")
set(CMAKE_CXX_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")



