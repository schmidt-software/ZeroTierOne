# vim: ft=dockerfile

FROM debian:stable-slim

LABEL maintainer "Michael Schmidt <schmidt.software@gmail.com>"

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
        iftop \
        ethtool

COPY entrypoint.sh.release /entrypoint.sh
RUN chmod 755 /entrypoint.sh

CMD []
ENTRYPOINT ["/entrypoint.sh"]
