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
    TARGET_ARCH := -m64
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_6D5AAF4E=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../app/JuceLibraryCode -I ../../../../externals/juce_git/modules -I ../../../../ -I ../../../../externals/juce_3.0.4/
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_6D5AAF4E=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../app/JuceLibraryCode -I ../../../../externals/juce_git/modules -I ../../../../ -I ../../../../externals/juce_3.0.4/
  TARGET := PimpMyP2PClient
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := ../../bin/linux

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_6D5AAF4E=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../app/JuceLibraryCode -I ../../../../externals/juce_git/modules -I ../../../../ -I ../../../../externals/juce_3.0.4/
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_6D5AAF4E=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../app/JuceLibraryCode -I ../../../../externals/juce_git/modules -I ../../../../ -I ../../../../externals/juce_3.0.4/
  TARGET := PimpMyP2PClient
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/peer_file_837f18c1.o \
  $(OBJDIR)/message_handler_6c74c9f9.o \
  $(OBJDIR)/pimp_message_26a170e7.o \
  $(OBJDIR)/socket_thread_8b901c15.o \
  $(OBJDIR)/component_window_77ab82d.o \
  $(OBJDIR)/look_and_feel_6b86d11d.o \
  $(OBJDIR)/peer_file_manager_9388bd17.o \
  $(OBJDIR)/peer_job_thread_c9ccbaf9.o \
  $(OBJDIR)/peer_message_handler_305fde4f.o \
  $(OBJDIR)/peer_processor_8e4029cf.o \
  $(OBJDIR)/peer_ui_1570a2f6.o \
  $(OBJDIR)/pimp_table_c68e2030.o \
  $(OBJDIR)/Main_ea31d1dc.o \
  $(OBJDIR)/juce_core_83c62e58.o \
  $(OBJDIR)/juce_cryptography_b9a4fcb2.o \
  $(OBJDIR)/juce_data_structures_227d5014.o \
  $(OBJDIR)/juce_events_db69aecc.o \
  $(OBJDIR)/juce_graphics_6dc24830.o \
  $(OBJDIR)/juce_gui_basics_b38617ac.o \
  $(OBJDIR)/juce_gui_extra_29a24434.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking PimpMyP2PClient
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning PimpMyP2PClient
	@$(CLEANCMD)

strip:
	@echo Stripping PimpMyP2PClient
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

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

$(OBJDIR)/component_window_77ab82d.o: ../../../common/ui/component_window.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling component_window.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/look_and_feel_6b86d11d.o: ../../../common/ui/look_and_feel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling look_and_feel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/peer_file_manager_9388bd17.o: ../../src/core/peer_file_manager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling peer_file_manager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/peer_job_thread_c9ccbaf9.o: ../../src/core/peer_job_thread.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling peer_job_thread.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/peer_message_handler_305fde4f.o: ../../src/core/peer_message_handler.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling peer_message_handler.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/peer_processor_8e4029cf.o: ../../src/core/peer_processor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling peer_processor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/peer_ui_1570a2f6.o: ../../src/ui/peer_ui.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling peer_ui.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pimp_table_c68e2030.o: ../../src/ui/pimp_table.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pimp_table.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_ea31d1dc.o: ../../app/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
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

$(OBJDIR)/juce_graphics_6dc24830.o: ../../../../externals/juce_git/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_b38617ac.o: ../../../../externals/juce_git/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_29a24434.o: ../../../../externals/juce_git/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
