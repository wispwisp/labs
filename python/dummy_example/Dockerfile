FROM ubuntu:latest

RUN apt update && apt install -y python3 python3-pip

RUN python3 -m pip install --upgrade pip && pip3 install \
  pandas sklearn numpy scipy statsmodels pytest

RUN useradd -ms /bin/bash me
WORKDIR /home/me

ADD ./*.py ./
RUN chown -R me:me *.py
RUN chmod 0644 *.py

USER me
ENTRYPOINT ["py.test"]

# docker build -t my/smth .
# docker run --rm --name=smth my/smth
