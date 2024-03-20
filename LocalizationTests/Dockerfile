# our local base image
FROM ubuntu 

LABEL description="Container for use with Visual Studio" 

ENV USERNAME LocalizationTests
ENV TESTDIR /home/${USERNAME}
ENV REPOS_PATH  /home/tesseract_repos

# install build dependencies 
RUN apt-get update && apt-get install -y g++ rsync zip openssh-server make gdb
RUN apt-get install bc 
RUN apt-get install build-essential
RUN apt install unzip
#Tesseract dependencies
RUN apt-get install g++ # or clang++ (presumably) -y
RUN apt-get install autoconf automake libtool -y
RUN apt-get install pkg-config -y
RUN apt-get install libpng-dev -y
RUN apt-get install libjpeg62-turbo-dev -y
RUN apt-get install libtiff5-dev -y
RUN apt-get install zlib1g-dev -y
RUN apt-get install libicu-dev -y
RUN apt-get install libpango1.0-dev -y
RUN apt-get install libcairo2-dev -y 
RUN apt-get install libleptonica-dev -y

#Python libraries 
RUN apt-get install python3.11.2
RUN apt-get install python3-pip
RUN pip install --upgrade pip
RUN pip install -U scikit-learn

RUN mkdir $REPOS_PATH
RUN mkdir $REPOS_PATH/langdata
#CLONING  TESSERACT REPOSITORIES

RUN git clone https://github.com/tesseract-ocr/tesstrain  $REPOS_PATH/tesstrain
WORKDIR $REPOS_PATH/tesstrain
RUN cd $REPOS_PATH/tesstrain
#Checking tesstrain working version
RUN git checkout 43ff10012af31914bb5b72304d9c21c8fdf4f464

RUN git clone https://github.com/tesseract-ocr/tesseract $REPOS_PATH/tesseract
WORKDIR $REPOS_PATH/tesseract
#Checking to tesseract version 5.2
RUN cd $REPOS_PATH/tesseract
RUN git checkout 5.2.0

#Lenguage traineddata models
RUN git clone https://github.com/tesseract-ocr/tessdata_best $REPOS_PATH/tessdata_best

#Training Text for lenguages
RUN git clone https://github.com/tesseract-ocr/langdata_lstm $REPOS_PATH/langdata_lstm
   
WORKDIR $REPOS_PATH/tesseract
RUN  ./autogen.sh
RUN  ./configure --disable-debug 'CXXFLAGS=-g -O3'

#Bulding tesseract
#use lscpu | egrep 'Model name|Socket|Thread|NUMA|CPU\(s\)' to get number of threads and use them all in MAKE commands. 
#or if you're using Windows, go to task Manager, Performance tab and the Logical Processors field  indicates number of threads. 
#In my case I have, 6 cores which means 12 threads. 
RUN make -j8
RUN make install
RUN ldconfig
RUN make training-install -j8
RUN tesseract -v


#Register all fonts in folder fonts
COPY ./fonts/ /usr/local/share/fonts
RUN fc-cache -f -v

RUN echo 'alias ls="ls -l --color=auto"' >> ~/.bashrc

WORKDIR /home

# configure SSH for communication with Visual Studio 
RUN mkdir -p /var/run/sshd

RUN echo 'PasswordAuthentication yes' >> /etc/ssh/sshd_config && \ 
   ssh-keygen -A 

# expose port 22 
EXPOSE 22

# RUN useradd -m -d ${TESTDIR} -s /bin/bash -G sudo ${USERNAME}


