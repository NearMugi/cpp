# !/bin/bash

source .env

#cd ${TARGET}
echo "-----------------------------"
echo " BUILD "
echo "-----------------------------"
docker build -t cpp-env:1.0 --build-arg TARGET_FOLDER=${TARGET_FOLDER} --build-arg TARGET_FILE=${TARGET_FILE} .
echo "-----------------------------"
echo " RUN "
echo "-----------------------------"
docker run  --name cpp -it cpp-env:1.0
docker rm -f cpp &> /dev/null