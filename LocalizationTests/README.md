https://devblogs.microsoft.com/cppblog/build-c-applications-in-a-linux-docker-container-with-visual-studio/


docker build -t localizationtests .
docker run -p 5000:22 -i -t localizationtests /bin/bash

service ssh start 
useradd -m -d /home/localizationtests -s /bin/bash -G sudo localizationtests
passwd localizationtests