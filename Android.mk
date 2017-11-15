include $(CLEAR_VARS)


LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog -lz -landroid
LOCAL_MODULE    := gcanvas

LOCAL_CFLAGS += -fPIC 


LOCAL_SRC_FILES :=  gcanvas/gcanvas.cpp \
					gcanvas/elf_sym_reader.cpp 


include $(BUILD_SHARED_LIBRARY)
