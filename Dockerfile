FROM ubuntu
# Колесников Борис, группа 221-329
ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools -y
RUN apt-get install build-essential -y

WORKDIR /group_Kolesnikov_Boris/
COPY *.cpp .
COPY *.h .
COPY *.pro .

RUN qmake echoServer.pro
RUN make

ENTRYPOINT ["./echoServer"]