# gameServer
команды Docker:

docker build -t echoserver .

docker run -it --rm -p 33333:33333 --name gameserver echoserver
