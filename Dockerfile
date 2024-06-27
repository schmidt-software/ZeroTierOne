# vim: ft=dockerfile

# FROM ubuntu:24.04 as stage

# RUN apt-get update -qq \
#     && apt-get -qq install \
#         curl \
#         make \
#         clang \
#     && curl --proto '=https' --tlsv1.3 https://sh.rustup.rs -sSf | sh
# COPY . .
# RUN /usr/bin/make
# RUN echo $PWD
# RUN cp zerotier-one /usr/sbin

#FROM ubuntu:22.04
FROM debian:stable-slim

COPY ./zerotier-one /usr/sbin
RUN ln -sf /usr/sbin/zerotier-one /usr/sbin/zerotier-idtool
RUN ln -sf /usr/sbin/zerotier-one /usr/sbin/zerotier-cli

RUN echo "${VERSION}" > /etc/zerotier-version
RUN rm -rf /var/lib/zerotier-one

RUN apt-get update \
    && apt-get install -y \
        curl \
        iproute2 \
        net-tools \
        fping \
        2ping \
        iputils-ping \
        iputils-arping \
        openssl \
        libssl1.1
# RUN apt-get update \
#     && apt-get install -y \
#         iproute2 \
#         net-tools \
#         fping \
#         2ping \
#         iputils-ping \
#         iputils-arping

COPY entrypoint.sh.release /entrypoint.sh
RUN chmod 755 /entrypoint.sh

CMD []
ENTRYPOINT ["/entrypoint.sh"]
