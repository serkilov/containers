FROM alpine:latest

RUN apk add --no-cache build-base

RUN mkdir /var/xxx/
RUN chmod 777 /var/xxx

COPY ./src/nummem.c /var/xxx/
COPY ./src/mem.c /var/xxx/
COPY ./src/cpu.c /var/xxx/
COPY ./src/run.sh /var/xxx/

WORKDIR /var/xxx/ 

RUN chmod +x run.sh

ENTRYPOINT ["./run.sh"]
