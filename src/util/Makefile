sub_dir = $(shell ls -l | grep ^d | awk '{print $$9}')
root_src = $(wildcard *.cc)
root_obj = $(patsubst %.cc, %.o, $(root_src))

all:$(sub_dir) $(root_obj)

$(sub_dir):ECHO
	@make -C $@

$(root_obj):%.o:%.cc
	$(CXX) -c $^ -o $(root_dir)/$(obj_dir)/$@ $(cxx_flag)

ECHO:
	@echo $(sub_dir)


