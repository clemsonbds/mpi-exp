FROM ubuntu:vivid

RUN apt-get update && apt-get install -y --no-install-recommends \
  gcc \
  openssh-server \
  openmpi-bin \
  libopenmpi-dev \
  && apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN mkdir /var/run/sshd
RUN echo 'root:asdf' | chpasswd
RUN sed -i 's/PermitRootLogin without-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# SSH login fix. Otherwise user is kicked off after login
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

ENV USER rakurai

RUN adduser --disabled-password --gecos "" $USER
RUN echo $USER:asdf | chpasswd
ENV HOME /home/$USER
WORKDIR $HOME

COPY hosts /tmp/hosts
RUN perl -pi -e 's:/etc/hosts:/tmp/hosts:g' /lib/x86_64-linux-gnu/libnss_files.so.2

COPY config .ssh/config
COPY id_rsa .ssh/id_rsa
COPY id_rsa.pub .ssh/authorized_keys
RUN chmod 600 .ssh/*
RUN chmod 644 .ssh/config

ADD machinefile machinefile

ADD barrier/barrier_test.c barrier_test.c
RUN mpicc -std=gnu99 -o barrier_test barrier_test.c
ADD stream/stream.c stream.c
RUN mpicc -std=gnu99 -o stream stream.c

RUN chgrp -R $USER $HOME
RUN chown -R $USER $HOME

CMD ["/usr/sbin/sshd", "-D"]
