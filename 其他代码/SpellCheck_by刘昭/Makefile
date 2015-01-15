SRC_DIR:=./src
INC_DIR:=./include
EXE_DIR:=./bin
CPPFLAGS := -g -o
CC:=g++
TARGET:=$(EXE_DIR)/main
OBJS:=$(SRC_DIR)/testmain.cpp $(SRC_DIR)/MyThread.cpp $(SRC_DIR)/MyTask.cpp $(SRC_DIR)/MyCacheThread.cpp
$(TARGET):$(OBJS) $(INC_DIR)/Thread.h $(INC_DIR)/MyThread.h $(INC_DIR)/MyLock.h $(INC_DIR)/MyCondition.h $(INC_DIR)/MyTask.h $(INC_DIR)/ThreadPool.h $(INC_DIR)/MySocket.h $(INC_DIR)/MyConf.h $(INC_DIR)/MyCache.h $(INC_DIR)/MyCacheThread.h
	$(CC) $(CPPFLAGS) $@ $(OBJS) -I$(INC_DIR) -lpthread -Wno-deprecated
