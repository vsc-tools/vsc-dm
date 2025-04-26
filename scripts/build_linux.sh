#!/bin/sh -x

yum install -y ninja-build

echo "BUILD_NUM=${BUILD_NUM}" >> python/vsc_dm/__build_num__.py
${IVPM_PYTHON} -m pip install ivpm cython setuptools --pre
${IVPM_PYTHON} -m ivpm update -a --py-prerls-packages

PYTHON=./packages/python/bin/python
${PYTHON} -m pip install twine auditwheel ninja wheel cython
${PYTHON} setup.py bdist_wheel

for whl in dist/*.whl; do
    ${PYTHON} -m auditwheel repair --only-plat $whl
    rm $whl
done
