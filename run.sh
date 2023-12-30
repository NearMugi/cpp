# !/bin/bash

source .env

#cd ${TARGET}
echo "-----------------------------"
echo " BUILD "
echo "-----------------------------"

docker build -t cpp-env:1.0 \
--build-arg TARGET_FOLDER=${TARGET_FOLDER} \
--build-arg TARGET_FILE=${TARGET_FILE} . \
> build.log 2>&1

 
if grep -q "ERROR" build.log; then
  echo "build Error..."
  cat build.log | tail -n 20
  exit 1
else
  echo "OK"
fi

echo "-----------------------------"
echo " RUN "
echo "-----------------------------"
docker run  --name cpp -it cpp-env:1.0
docker rm -f cpp &> /dev/null

exit 0