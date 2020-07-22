
import os
import sys, os.path, platform, warnings
from distutils import log
from distutils.core import setup
from distutils.core import Distribution as _Distribution
from distutils.core import Extension as _Extension
from distutils.dir_util import mkpath
from distutils.command.build_ext import build_ext as _build_ext
from distutils.command.bdist_rpm import bdist_rpm as _bdist_rpm
from distutils.errors import DistutilsError, CompileError, LinkError, DistutilsPlatformError

if 'setuptools.extension' in sys.modules:
    _Extension = sys.modules['setuptools.extension']._Extension
    sys.modules['distutils.core'].Extension = _Extension
    sys.modules['distutils.extension'].Extension = _Extension
    sys.modules['distutils.command.build_ext'].Extension = _Extension

ith_cython = False
if 'sdist' in sys.argv:
    # we need cython here
    with_cython = True
try:
    from Cython.Distutils.extension import Extension as _Extension
    from Cython.Distutils import build_ext as _build_ext
    with_cython = True
except ImportError:
    if with_cython:
        raise

try:
    from wheel.bdist_wheel import bdist_wheel
except ImportError:
    bdist_wheel = None

python_dir=os.path.dirname(os.path.abspath(__file__))
libvsc_dir=os.path.dirname(python_dir)

class Distribution(_Distribution):

    def __init__(self, attrs=None):
        _Distribution.__init__(self, attrs)
        if not self.ext_modules:
            return
        for idx in range(len(self.ext_modules)-1, -1, -1):
            ext = self.ext_modules[idx]
            if not isinstance(ext, Extension):
                continue
            setattr(self, ext.attr_name, None)
            self.global_options = [
                    (ext.option_name, None,
                        "include %s (default if %s is available)"
                        % (ext.feature_description, ext.feature_name)),
                    (ext.neg_option_name, None,
                        "exclude %s" % ext.feature_description),
            ] + self.global_options
            self.negative_opt = self.negative_opt.copy()
            self.negative_opt[ext.neg_option_name] = ext.option_name

    def has_ext_modules(self):
        if not self.ext_modules:
            return False
        for ext in self.ext_modules:
            with_ext = self.ext_status(ext)
            if with_ext is None or with_ext:
                return True
        return False

    def ext_status(self, ext):
        implementation = platform.python_implementation()
        if implementation != 'CPython':
            return False
        if isinstance(ext, Extension):
            with_ext = getattr(self, ext.attr_name)
            return with_ext
        else:
            return True
        
class Extension(_Extension):

    def __init__(self, name, sources, feature_name, feature_description,
            feature_check, **kwds):
        if not with_cython:
            for filename in sources[:]:
                base, ext = os.path.splitext(filename)
                if ext == '.pyx':
                    sources.remove(filename)
                    sources.append('%s.cpp' % base)
        _Extension.__init__(self, name, sources, **kwds)
        self.feature_name = feature_name
        self.feature_description = feature_description
        self.feature_check = feature_check
        self.attr_name = 'with_' + feature_name.replace('-', '_')
        self.option_name = 'with-' + feature_name
        self.neg_option_name = 'without-' + feature_name


class build_ext(_build_ext):

    def run(self):
        optional = True
        disabled = True
        for ext in self.extensions:
            with_ext = self.distribution.ext_status(ext)
            if with_ext is None:
                disabled = False
            elif with_ext:
                optional = False
                disabled = False
                break
        if disabled:
            return
        try:
            _build_ext.run(self)
        except DistutilsPlatformError:
            exc = sys.exc_info()[1]
            if optional:
                log.warn(str(exc))
                log.warn("skipping build_ext")
            else:
                raise

    def get_source_files(self):
        self.check_extensions_list(self.extensions)
        filenames = []
        for ext in self.extensions:
            if with_cython:
                self.cython_sources(ext.sources, ext)
            for filename in ext.sources:
                filenames.append(filename)
                base = os.path.splitext(filename)[0]
                for ext in ['c', 'h', 'pyx', 'pxd']:
                    filename = '%s.%s' % (base, ext)
                    if filename not in filenames and os.path.isfile(filename):
                        filenames.append(filename)
        return filenames

    def get_outputs(self):
        self.check_extensions_list(self.extensions)
        outputs = []
        for ext in self.extensions:
            fullname = self.get_ext_fullname(ext.name)
            filename = os.path.join(self.build_lib,
                                    self.get_ext_filename(fullname))
            if os.path.isfile(filename):
                outputs.append(filename)
        return outputs

    def build_extensions(self):
        self.check_extensions_list(self.extensions)
        for ext in self.extensions:
            with_ext = self.distribution.ext_status(ext)
            if with_ext is not None and not with_ext:
                continue
            if with_cython:
                ext.sources = self.cython_sources(ext.sources, ext)
            try:
                self.build_extension(ext)
            except (CompileError, LinkError):
                if with_ext is not None:
                    raise
                log.warn("Error compiling module, falling back to pure Python")

cmdclass = {
    'build_ext': build_ext
#    'bdist_rpm': bdist_rpm
}
if bdist_wheel:
    cmdclass['bdist_wheel'] = bdist_wheel
    
VERSION="0.0.1"
PLATFORMS = "Any"

LIBVSC_CHECK = """
#include "libvsc.h"

int main(void) {

    return 0;
}
"""

setup(
    name="libvsc",
    version=VERSION,
    platforms=PLATFORMS,
    ext_modules=[
        Extension("libvsc", [
            'libvsc.pyx'
            ],
            'libvsc', 'LibVSC Bindings', LIBVSC_CHECK,
            include_dirs=[
                '/usr/include',
                os.path.join(libvsc_dir, "src"),
                os.path.join(libvsc_dir, "src", "constraints"),
                os.path.join(libvsc_dir, "src", "datamodel"),
                os.path.join(libvsc_dir, "src", "expr"),
                os.path.join(libvsc_dir, "src", "solver")
                ],
            library_dirs=[
                "/usr/lib",
                os.path.join(libvsc_dir, "build", "src")
                ],
            language="c++",
            libraries=['vsc']),
        ],
        distclass=Distribution,
        cmdclass=cmdclass,
    )

