# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := ../../bin/linux

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=armv6
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_4BD83949=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../JuceLibraryCode -I ../../../../externals/juce_git/modules -I ../../../../ -I ../../../../externals/juce_3.0.4/
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -ldl -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_4BD83949=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../JuceLibraryCode -I ../../../../externals/juce_git/modules -I ../../../../ -I ../../../../externals/juce_3.0.4/
  TARGET := PimpMyP2P_TrackerCmd_d
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := ../../bin/linux

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=armv6
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_4BD83949=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../JuceLibraryCode -I ../../../../externals/juce_git/modules -I ../../../../ -I ../../../../externals/juce_3.0.4/
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -ldl -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_4BD83949=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../JuceLibraryCode -I ../../../../externals/juce_git/modules -I ../../../../ -I ../../../../externals/juce_3.0.4/
  TARGET := PimpMyP2P_TrackerCmd
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/Main_e223237d.o \
  $(OBJDIR)/peer_file_837f18c1.o \
  $(OBJDIR)/message_handler_6c74c9f9.o \
  $(OBJDIR)/pimp_message_26a170e7.o \
  $(OBJDIR)/socket_thread_8b901c15.o \
  $(OBJDIR)/tracker_file_manager_966083ab.o \
  $(OBJDIR)/tracker_job_thread_2b4d168d.o \
  $(OBJDIR)/tracker_message_handler_46d9f3b.o \
  $(OBJDIR)/tracker_processor_ec3c0bbb.o \
  $(OBJDIR)/juce_core_83c62e58.o \
  $(OBJDIR)/juce_cryptography_b9a4fcb2.o \
  $(OBJDIR)/juce_data_structures_227d5014.o \
  $(OBJDIR)/juce_events_db69aecc.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking PimpMyP2P_TrackerCmd
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning PimpMyP2P_TrackerCmd
	@$(CLEANCMD)

strip:
	@echo Stripping PimpMyP2P_TrackerCmd
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/Main_e223237d.o: ../Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/peer_file_837f18c1.o: ../../../common/files/peer_file.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling peer_file.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/message_handler_6c74c9f9.o: ../../../common/messages/message_handler.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling message_handler.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pimp_message_26a170e7.o: ../../../common/messages/pimp_message.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pimp_message.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/socket_thread_8b901c15.o: ../../../common/network/socket_thread.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling socket_thread.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/tracker_file_manager_966083ab.o: ../../src/core/tracker_file_manager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling tracker_file_manager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/tracker_job_thread_2b4d168d.o: ../../src/core/tracker_job_thread.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling tracker_job_thread.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/tracker_message_handler_46d9f3b.o: ../../src/core/tracker_message_handler.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling tracker_message_handler.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/tracker_processor_ec3c0bbb.o: ../../src/core/tracker_processor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling tracker_processor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_83c62e58.o: ../../../../externals/juce_git/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_cryptography_b9a4fcb2.o: ../../../../externals/juce_git/modules/juce_cryptography/juce_cryptography.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_227d5014.o: ../../../../externals/juce_git/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_db69aecc.o: ../../../../externals/juce_git/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
