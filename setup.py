#****************************************************************************
#* setup.py for vsc-dm
#****************************************************************************
import os
import sys
import platform
from setuptools import Extension, find_namespace_packages

if "IVPM_PYTHONPATH" in os.environ.keys():
    ps = ";" if platform.system() == "Windows" else ":"
    for i,p in enumerate(os.environ["IVPM_PYTHONPATH"].split(ps)):
        sys.path.insert(i, p)

version="0.0.1"

proj_dir = os.path.dirname(os.path.abspath(__file__))

try:
    import sys
    sys.path.insert(0, os.path.join(proj_dir, "python"))
    from vsc_dm.__build_num__ import BUILD_NUM
    version += ".%s" % str(BUILD_NUM)
except ImportError:
    pass

isSrcBuild = False

try:
    from ivpm.setup import setup
    isSrcBuild = os.path.isdir(os.path.join(proj_dir, "src"))
    print("vsc-dm: running IVPM SrcBuild")
except ImportError as e:
    from setuptools import setup
    print("vsc-dm: running non-src build (%s)" % str(e))

if isSrcBuild:
    incdir = os.path.join(proj_dir, "src", "include")
else:
    incdir = os.path.join(proj_dir, "python/vsc_dm/share/include")

vsc_dir = proj_dir

ext = Extension("vsc_dm.core",
    sources=[
        os.path.join(vsc_dir, 'python', "core.pyx"), 
        os.path.join(vsc_dir, 'python', 'VisitorProxy.cpp'),
        os.path.join(vsc_dir, 'python', 'ModelFieldDataClosure.cpp'),
        os.path.join(vsc_dir, 'python', 'ModelStructCreateHookClosure.cpp'),
        os.path.join(vsc_dir, 'python', 'MkModelBuildContext.cpp'),
        os.path.join(vsc_dir, 'python', 'VscTasks.cpp'),
    ],
    language="c++",
    include_dirs=[incdir]
)
ext.cython_directives={'language_level' : '3'}

setup_args = dict(
  name = "vsc-dm",
  version=version,
  packages=find_namespace_packages(where='python'),
  package_dir = {'' : 'python'},
  package_data = {'vsc_dm': [
      'core.pxd',
      'decl.pxd'
      ]},
  author = "Matthew Ballance",
  author_email = "matt.ballance@gmail.com",
  description = ("Core Verification Stimulus and Coverage library"),
  long_description="""
  Provides a library for constrained randomization and coverage collection
  """,
  license = "Apache 2.0",
  keywords = ["SystemVerilog", "Verilog", "RTL", "Python"],
  url = "https://github.com/vsc-tools/vsc-dm",
  entry_points={
    'ivpm.pkginfo': [
        'vsc-dm = vsc_dm.pkginfo:PkgInfo'
    ]
  },
  install_requires=[
      'debug-mgr',
  ],
  setup_requires=[
    'setuptools_scm',
    'cython'
  ],
  ext_modules=[ ext ]
)

if isSrcBuild:
    setup_args["ivpm_extdep_pkgs"] = ["debug-mgr"]
    setup_args["ivpm_extra_data"] = {
        "vsc-dm": [
            ("src/include", "share"),
            ("build/{libdir}/{libpref}vsc-dm{dllext}", ""),
        ]
    }

setup(**setup_args)


