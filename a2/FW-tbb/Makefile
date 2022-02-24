include Makefile.include

INCLUDE_DIR = $(TBB_DIR)/include
LIBRARY_DIR = $(TBB_DIR)/build/$(LIBRARY_VER)

# CXX = g++
# To compile in clones:
CXX = g++
CXXFLAGS = -O3 -Wall -std=c++11 -DUSE_LAMBDAS -Wsign-compare 
LDFLAGS =
LIBS = -ltbb -lrt

CXXFLAGS += -I$(INCLUDE_DIR)
 
OBJS = fw.o fw_sr_task.o fw_tiled_task.o fw_tiled_flow_graph.o

all : $(OBJS)
	$(CXX) $(LDFLAGS) fw.o -o fw -L$(LIBRARY_DIR) $(LIBS)
	$(CXX) $(LDFLAGS) fw_sr_task.o -o fw_sr_task -L$(LIBRARY_DIR) $(LIBS)
	$(CXX) $(LDFLAGS) fw_tiled_task.o -o fw_tiled_task -L$(LIBRARY_DIR) $(LIBS)
	$(CXX) $(LDFLAGS) fw_tiled_flow_graph.o -o fw_tiled_flow_graph -L$(LIBRARY_DIR) $(LIBS)


%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean :
	rm -f fw fw_sr_task fw_tiled_task fw_tiled_flow_graph $(OBJS) makejob.err makejob.out
