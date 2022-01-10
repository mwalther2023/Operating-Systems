##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Project8
ConfigurationName      :=Debug
WorkspacePath          :=/media/sf_Operating_Systems/Op_Sys_Workspace
ProjectPath            :=/media/sf_Operating_Systems/Op_Sys_Workspace/Project8
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Matthew Walther
Date                   :=03/06/21
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
ObjectsFileList        :="Project8.txt"
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
Objects0=$(IntermediateDirectory)/PageTableEntry.cpp$(ObjectSuffix) $(IntermediateDirectory)/Process.cpp$(ObjectSuffix) $(IntermediateDirectory)/PagingSimulator.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Counter.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/PageTableEntry.cpp$(ObjectSuffix): PageTableEntry.cpp $(IntermediateDirectory)/PageTableEntry.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/sf_Operating_Systems/Op_Sys_Workspace/Project8/PageTableEntry.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PageTableEntry.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PageTableEntry.cpp$(DependSuffix): PageTableEntry.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PageTableEntry.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PageTableEntry.cpp$(DependSuffix) -MM PageTableEntry.cpp

$(IntermediateDirectory)/PageTableEntry.cpp$(PreprocessSuffix): PageTableEntry.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PageTableEntry.cpp$(PreprocessSuffix) PageTableEntry.cpp

$(IntermediateDirectory)/Process.cpp$(ObjectSuffix): Process.cpp $(IntermediateDirectory)/Process.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/sf_Operating_Systems/Op_Sys_Workspace/Project8/Process.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Process.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Process.cpp$(DependSuffix): Process.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Process.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Process.cpp$(DependSuffix) -MM Process.cpp

$(IntermediateDirectory)/Process.cpp$(PreprocessSuffix): Process.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Process.cpp$(PreprocessSuffix) Process.cpp

$(IntermediateDirectory)/PagingSimulator.cpp$(ObjectSuffix): PagingSimulator.cpp $(IntermediateDirectory)/PagingSimulator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/sf_Operating_Systems/Op_Sys_Workspace/Project8/PagingSimulator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PagingSimulator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PagingSimulator.cpp$(DependSuffix): PagingSimulator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PagingSimulator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PagingSimulator.cpp$(DependSuffix) -MM PagingSimulator.cpp

$(IntermediateDirectory)/PagingSimulator.cpp$(PreprocessSuffix): PagingSimulator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PagingSimulator.cpp$(PreprocessSuffix) PagingSimulator.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/sf_Operating_Systems/Op_Sys_Workspace/Project8/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/Counter.cpp$(ObjectSuffix): Counter.cpp $(IntermediateDirectory)/Counter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/sf_Operating_Systems/Op_Sys_Workspace/Project8/Counter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Counter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Counter.cpp$(DependSuffix): Counter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Counter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Counter.cpp$(DependSuffix) -MM Counter.cpp

$(IntermediateDirectory)/Counter.cpp$(PreprocessSuffix): Counter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Counter.cpp$(PreprocessSuffix) Counter.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


