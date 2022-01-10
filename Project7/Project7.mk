##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Project7
ConfigurationName      :=Debug
WorkspacePath          :=/media/sf_Operating_Systems/Op_Sys_Workspace
ProjectPath            :=/media/sf_Operating_Systems/Op_Sys_Workspace/Project7
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Matthew Walther
Date                   :=24/05/21
CodeLitePath           :=/home/matthew/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Project7.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS := -std=c++17 -Wall -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/MemoryChunk.cpp$(ObjectSuffix) $(IntermediateDirectory)/MemoryManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/MemoryChunk.cpp$(ObjectSuffix): MemoryChunk.cpp $(IntermediateDirectory)/MemoryChunk.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/sf_Operating_Systems/Op_Sys_Workspace/Project7/MemoryChunk.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MemoryChunk.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MemoryChunk.cpp$(DependSuffix): MemoryChunk.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MemoryChunk.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MemoryChunk.cpp$(DependSuffix) -MM MemoryChunk.cpp

$(IntermediateDirectory)/MemoryChunk.cpp$(PreprocessSuffix): MemoryChunk.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MemoryChunk.cpp$(PreprocessSuffix) MemoryChunk.cpp

$(IntermediateDirectory)/MemoryManager.cpp$(ObjectSuffix): MemoryManager.cpp $(IntermediateDirectory)/MemoryManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/sf_Operating_Systems/Op_Sys_Workspace/Project7/MemoryManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MemoryManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MemoryManager.cpp$(DependSuffix): MemoryManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MemoryManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MemoryManager.cpp$(DependSuffix) -MM MemoryManager.cpp

$(IntermediateDirectory)/MemoryManager.cpp$(PreprocessSuffix): MemoryManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MemoryManager.cpp$(PreprocessSuffix) MemoryManager.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/sf_Operating_Systems/Op_Sys_Workspace/Project7/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


