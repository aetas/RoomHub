FROM python:3.7.4-slim

ARG PIO_VERSION=4.0.3

VOLUME /workspace

RUN pip install -U platformio==${PIO_VERSION}

WORKDIR /workspace

entrypoint ["platformio"]

