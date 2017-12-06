FROM gcc

RUN apt-get update
RUN apt-get install -y libsdl-dev libboost-dev

WORKDIR /pso
