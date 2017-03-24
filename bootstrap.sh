#!/usr/bin/env bash

apt-get update && \
apt-get upgrade -y && \
apt-get install -y \
    autoconf \
    automake \
    g++ \
    libtool \
    autoconf-archive \
    make \
    libboost-all-dev \
    dkms \
    virtualbox-guest-utils

ln -sf /vagrant /home/ubuntu/code_portfolio
