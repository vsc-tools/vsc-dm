#!/bin/sh

docker pull quay.io/pypa/manylinux2014_x86_64

docker run -it -v `pwd`:/libvsc manylinux2014_x86_64 bash
