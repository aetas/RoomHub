FROM python:2.7

VOLUME /doc
WORKDIR /doc

RUN pip install mkdocs
RUN pip install mkdocs-material

EXPOSE 8000

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]

CMD ["serve"]

