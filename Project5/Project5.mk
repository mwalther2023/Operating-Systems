##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Project5
ConfigurationName      :=Debug
WorkspacePath          :=/media/sf_Operating_Systems/Op_Sys_Workspace
ProjectPath            :=/media/sf_Operating_Systems/Op_Sys_Workspace/Project5
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Matthew Walther
Date                   :=12/05/21
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
ObjectsFileList        :="Project5.txt"
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
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Process.cpp$(ObjectSuffix) $(IntermediateDirectory)/RR_Scheduler.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/sf_Operating_Systems/Op_Sys_Workspace/Project5/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/Process.cpp$(ObjectSuffix): Process.cpp $(IntermediateDirectory)/Process.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/sf_Operating_Systems/Op_Sys_Workspace/Project5/Process.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Process.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Process.cpp$(DependSuffix): Process.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Process.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Process.cpp$(DependSuffix) -MM Process.cpp

$(IntermediateDirectory)/Process.cpp$(PreprocessSuffix): Process.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Process.cpp$(PreprocessSuffix) Process.cpp

$(IntermediateDirectory)/RR_Scheduler.cpp$(ObjectSuffix): RR_Scheduler.cpp $(IntermediateDirectory)/RR_Scheduler.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/sf_Operating_Systems/Op_Sys_Workspace/Project5/RR_Scheduler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/RR_Scheduler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/RR_Scheduler.cpp$(DependSuffix): RR_Scheduler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/RR_Scheduler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/RR_Scheduler.cpp$(DependSuffix) -MM RR_Scheduler.cpp

$(IntermediateDirectory)/RR_Scheduler.cpp$(PreprocessSuffix): RR_Scheduler.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/RR_Scheduler.cpp$(PreprocessSuffix) RR_Scheduler.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


